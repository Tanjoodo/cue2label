#cue2label
cue2label can take a [.cue file](https://en.wikipedia.org/wiki/Cue_sheet_(computing\)), the associated file's length and generate an audacity style lables file that you can import to easily cut that file into smaller tracks.

This is useful for splitting the tracks of an audio CD image.

##Usage
First, run `make` to compile the program. You'll find the executable in `./obj` along with all the other object files.
Then, run the program passing it 4 arguments in this order: location of .cue file, where to save the lables, the length of the audio file in the format mm ss.
For example, `cue2label ~/myalbum.cue ~/albumlabels.txt 44 59` would generate a label file for an audio file with the length of 44 minutes and 59 seconds.

Once the label file is generated, you can [import them from audacity](http://manual.audacityteam.org/o/man/label_tracks.html#export)  and [split the file based on the labels](http://manual.audacityteam.org/o/man/file_menu.html#export_multiple).

##License
This project is licensed under the MIT license. More details in LICENSE.md
