import QtQuick 2.6
import Toou2D 1.0
import QtMultimedia 5.6


MediaPlayer{
    id:qmediaplayer;
    function mplay(url){
        source = url;
        play();
    }
}



