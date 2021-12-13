#################################################################################
#
# Library: QEXT
#
# Copyright (c) ChengXueWen. Contact: 1398831004@qq.com
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0.txt
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
#################################################################################

#--------------------------------------------------------------------------------
# Set lib base name and out put path
#--------------------------------------------------------------------------------
set(EXECUTABLE_OUTPUT_PATH ${QEXT_TEST_OUTPUT_DIR}/core/invoke)
set(LIBRARY_OUTPUT_PATH ${QEXT_TEST_OUTPUT_DIR}/core/invoke)


##--------------------------------------------------------------------------------
## Add test
##--------------------------------------------------------------------------------
qextFunctionCoreAddTest(qext_tst_corePointerFunctor TEST_SOURCE tst_qextPointerFunctor.cpp)
qextFunctionCoreAddTest(qext_tst_coreMemberFunctor TEST_SOURCE tst_qextMemberFunctor.cpp)
qextFunctionCoreAddTest(qext_tst_coreFunction TEST_SOURCE tst_qextFunction.cpp)
qextFunctionCoreAddTest(qext_tst_coreVisitor TEST_SOURCE tst_qextVisitor.cpp)
qextFunctionCoreAddTest(qext_tst_coreTrackable TEST_SOURCE tst_qextTrackable.cpp)
qextFunctionCoreAddTest(qext_tst_coreBindFunctor TEST_SOURCE tst_qextBindFunctor.cpp)
qextFunctionCoreAddTest(qext_tst_coreBindReturnFunctor TEST_SOURCE tst_qextBindReturnFunctor.cpp)
qextFunctionCoreAddTest(qext_tst_coreConnection TEST_SOURCE tst_qextConnection.cpp)
qextFunctionCoreAddTest(qext_tst_coreFunctorTrait TEST_SOURCE tst_qextFunctorTrait.cpp)
qextFunctionCoreAddTest(qext_tst_coreHideFunctor TEST_SOURCE tst_qextHideFunctor.cpp)
qextFunctionCoreAddTest(qext_tst_coreLambda TEST_SOURCE tst_qextLambda.cpp)
qextFunctionCoreAddTest(qext_tst_coreLimitReference TEST_SOURCE tst_qextLimitReference.cpp)
qextFunctionCoreAddTest(qext_tst_coreReturnTypeDeduce TEST_SOURCE tst_qextReturnTypeDeduce.cpp)
qextFunctionCoreAddTest(qext_tst_coreRetypeReturnFunctor TEST_SOURCE tst_qextRetypeReturnFunctor.cpp)
qextFunctionCoreAddTest(qext_tst_coreTrackObjectFunctor TEST_SOURCE tst_qextTrackObjectFunctor.cpp)
qextFunctionCoreAddTest(qext_tst_coreRetypeFunctor TEST_SOURCE tst_qextRetypeFunctor.cpp)
qextFunctionCoreAddTest(qext_tst_coreSignal TEST_SOURCE tst_qextSignal.cpp)
qextFunctionCoreAddTest(qext_tst_coreSlot TEST_SOURCE tst_qextSlot.cpp)

