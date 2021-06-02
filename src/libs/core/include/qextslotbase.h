#ifndef QEXTSLOTBASE_H
#define QEXTSLOTBASE_H

#include <qextglobal.h>
#include <qextfunctortrait.h>
#include <qexttrackable.h>

#include <QScopedPointer>

namespace qextinternal {

typedef void* (*HookFunctionType)(void*);


/** Internal representation of a slot.
 * Derivations of this class can be considered as a link
 * between a slot and the functor that the slot should
 * execute in operator(). This link is needed because the
 * slot doesn't necessarily have exactly the
 * same function signature as the functor thus allowing for
 * implicit conversions.
 * The base class QEXTSlotRep serves the purpose to
 * - form a common pointer type (QEXTSlotRep*),
 * - offer the possibility to create duplicates (deepCopy()),
 * - offer a notification callback (notify()),
 * - implement some of QEXTSlotBase's interface that depends
 *   on the notification callback, i.e.
 *   -# the possibility to set a single parent with a callback
 *      (setParent()) that is executed from notify(),
 *   -# a generic function pointer, m_call, that is simply
 *      set to zero in notify() to invalidate the slot.
 * m_slotRep inherits trackable so that connection objects can
 * refer to the slot and are notified when the slot is destroyed.
 */
struct QEXT_CORE_API QEXTSlotRep : public QEXTTrackable
{
    QEXTSlotRep(HookFunctionType call, HookFunctionType destroy, HookFunctionType deepCopy);
    ~QEXTSlotRep();

    // only MSVC needs this to guarantee that all new/delete are executed from the DLL module
#ifdef Q_CC_MSVC
    void *operator new(size_t size);
    void operator delete(void *p);
#endif
    /** Destroys the QEXTSlotRep object (but doesn't delete it).
     */
    void destroy();

    /** Makes a deep copy of the QEXTSlotRep object.
     * @return A deep copy of the QEXTSlotRep object.
     */
    QEXTSlotRep *deepCopy() const;

    /** Set the parent with a callback.
     * slots have one parent exclusively.
     * @param parent The new parent.
     * @param cleanup The callback to execute from notify().
     */
    void setParent(void *parent, HookFunctionType cleanup);

    // Invalidates the slot and executes the parent's cleanup callback.
    void disconnect();

    /** Callback that invalidates the slot.
     * This callback is registered in every object of a trackable
     * inherited type that is referred by this QEXTSlotRep object.
     * It is executed when the slot becomes invalid because of some
     * referred object dying.
     * @param data The QEXTSlotRep object that is becoming invalid (@p this).
     */
    static void *notify(void *data);

    // Callback that invokes the contained functor.
    /** This can't be a virtual function since number of arguments
     * must be flexible. We use function pointers to QEXTSlotCall::callIt()
     * instead. m_call is set to zero to indicate that the slot is invalid.
     */
    HookFunctionType m_call;

    // Callback that detaches the slot_rep object from referred trackables and destroys it.
    /** This could be a replaced by a virtual dtor. However since this struct is
     * crucual for the efficiency of the whole library we want to avoid this.
     */
    HookFunctionType m_destroy;

    /** Callback that makes a deep copy of the QEXTSlotRep object.
     * @return A deep copy of the QEXTSlotRep object.
     */
    HookFunctionType m_deepCopy;

    /** Callback of m_parent. */
    HookFunctionType m_cleanup;

    /** Parent object whose callback m_cleanup is executed on notification. */
    void *m_parent;
};

/** Functor used to add a dependency to a trackable.
 * Consequently QEXTSlotRep::notify() gets executed when the
 * trackable is destroyed or overwritten.
 */
struct QEXT_CORE_API QEXTSlotDoBind
{
    /** Construct a QEXTSlotRep functor.
     * @param rep The QEXTSlotRep object trackables should notify on destruction.
     */
    QEXTSlotDoBind(QEXTSlotRep *rep) : m_slotRep(rep) {}

    /** Adds a dependency to @p trackable.
     * @param t The trackable object to add a callback to.
     */
    void operator()(const QEXTTrackable *trackable) const {
        trackable->addDestroyNotifyCallback(m_slotRep, &QEXTSlotRep::notify);
    }

    /** The QEXTSlotRep object trackables should notify on destruction. */
    QEXTSlotRep *m_slotRep;
};

/** Functor used to remove a dependency from a trackable.
 */
struct QEXT_CORE_API QEXTSlotDoUnbind
{
    /** Construct a QEXTSlotDoUnbind functor.
     * @param rep The QEXTSlotRep object trackables don't need to notify on destruction any more.
     */
    QEXTSlotDoUnbind(QEXTSlotRep *rep) : m_slotRep(rep) {}

    /** Removes a dependency from @p trackable.
     * @param trackable The trackable object to remove the callback from.
     */
    void operator()(const QEXTTrackable *trackable) const {
        trackable->removeDestroyNotifyCallback(m_slotRep);
    }

    /** The QEXTSlotRep object trackables don't need to notify on destruction any more. */
    QEXTSlotRep *m_slotRep;
};

} //namespace qextinternal


/** @defgroup slot Slots
 * Slots are type-safe representations of callback methods and functions.
 * A Slot can be constructed from any function object or function, regardless of
 * whether it is a global function, a member method, static, or virtual.
 *
 * Use the qextMemberFunctor() and qextPointerFunctor() template functions to get a QEXTSlot, like so:
 *
 * @code
 * QEXTSlot<void, int> slot = qextMemberFunctor(someobj, &SomeClass::somemethod);
 * @endcode
 *
 * or
 *
 * @code
 * QEXTSlot<void, int> slot = qextPointerFunctor(&somefunction);
 * @endcode
 *
 * or
 *
 * @code
 * m_Button.signal_clicked().connect( qextMemberFunctor(*this, &MyWindow::on_button_clicked) );
 * @endcode
 *
 * The compiler will complain if SomeClass::somemethod, etc. have the wrong signature.
 *
 * You can also pass slots as method parameters where you might normally pass a function pointer.
 *
 * A C++11 lambda expression is a functor (function object). It is automatically
 * wrapped in a slot, if it is connected to a signal.
 * @code
 * auto on_response = [&someobj] (int response_id)
 *   {
 *     someobj.somemethod(response_id);
 *     somefunction(response_id);
 *   };
 * m_Dialog.signal_response().connect(on_response);
 * @endcode
 *
 * If you connect a C++11 lambda expression or a std::function<> instance to
 * a signal or assign it to a slot,
 * - if the return type is not void, you must use the #QEXT_FUNCTORS_DEDUCE_RESULT_TYPE_WITH_DECLTYPE macro,
 * - if your functor contains references to QEXTTrackable derived objects,
 *   those objects will not be tracked, unless you also use qextTrackObjectFunctor().
 *
 * @ingroup sigcfunctors
 */


/** Base type for slots.
 * QEXTSlotBase integrates most of the interface of the derived
 * QEXTSlot templates. slots
 * can be connected to signals, be disconnected at some later point
 * (disconnect()) and temporarily be blocked (block(), unblock()).
 * The validity of a slot can be tested with isEmpty().
 *
 * The internal representation of a qextinternal::QEXTSlotRep derived
 * type is built from QEXTSlotBase's derivations. setParent() is used to
 * register a notification callback that is executed when the slot gets
 * invalid. addDestroyNotifyCallback() is used by connection objects
 * to add a notification callback that is executed on destruction.
 *
 * @ingroup slot
 */
class QEXT_CORE_API QEXTSlotBase : public QEXTFunctorBase
{
    typedef qextinternal::QEXTSlotRep SlotRepType;
public:
    typedef QEXTTrackable::DestroyNotifyFunc DestroyNotifyFunc;

    // Constructs an empty slot.
    QEXTSlotBase();
    /** Constructs a slot from an existing SlotRepType object.
     * @param rep The SlotRepType object this slot should contain.
     */
    explicit QEXTSlotBase(SlotRepType *rep);
    /** Constructs a slot, copying an existing one.
     * @param src The existing slot to copy.
     */
    QEXTSlotBase(const QEXTSlotBase &src);
    ~QEXTSlotBase();

    /** Tests whether a slot is null, because the default constructor was used.
     * Test a slot for null like so:
     * @code
     * if(slot)
     *  do_something()
     * @endcode
     */
    operator bool() const;

    /** Overrides this slot making a copy from another slot.
     * @param src The slot from which to make a copy.
     * @return @p this.
     */
    QEXTSlotBase& operator=(const QEXTSlotBase &src);

    /** Sets the parent of this slot.
     * This function is used by signals to register a notification callback.
     * This notification callback is executed when the slot becomes invalid
     * because of some referred object dying.
     * @param parent The new parent.
     * @param cleanup The notification callback.
     */
    void setParent(void *parent, void*(*cleanup)(void*)) const;

    /** Add a callback that is executed (notified) when the slot is detroyed.
     * This function is used internally by connection objects.
     * @param data Passed into func upon notification.
     * @param func Callback executed upon destruction of the object.
     */
    void addDestroyNotifyCallback(void *data, DestroyNotifyFunc func) const;

    /** Remove a callback previously installed with addDestroyNotifyCallback().
     * The callback is not executed.
     * @param data Parameter passed into previous call to addDestroyNotifyCallback().
     */
    void removeDestroyNotifyCallback(void *data) const;

    /** Returns whether the slot is invalid.
     * @return @p true if the slot is invalid (empty).
     */
    bool isEmpty() const;

    /** Returns whether the slot is blocked.
     * @return @p true if the slot is blocked.
     */
    bool isBlocked() const;

    /** Sets the blocking state.
     * If @e block is @p true then the blocking state is set.
     * Subsequent calls to QEXTSlot::operator()() don't invoke the functor
     * contained by this slot until unblock() or block() with
     * @e block = @p false is called.
     * @param block Indicates whether the blocking state should be set or unset.
     * @return @p true if the slot was in blocking state before.
     */
    bool setBlock(bool block = true);

    /** Unsets the blocking state.
     * @return @p true if the slot was in blocking state before.
     */
    bool unblock();

    /** Disconnects the slot.
     * Invalidates the slot and notifies the parent.
     */
    void disconnect();

public:
    /** Typed SlotRepType object that contains a functor. */
    mutable QScopedPointer<SlotRepType> m_slotRep;
    /** Indicates whether the slot is blocked. */
    bool m_blocked;
};


#endif // QEXTSLOTBASE_H
