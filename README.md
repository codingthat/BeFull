# BeFull
Full-screen app launcher for BeOS / Haiku OS.

BeFull for BeOS 0.04 Source Code, by Kevin Field
------------------------------------------

Thank you to everyone who e-mailed me, and especially to Jason Kilburn Evans, who generously donated the icons.

What is it?
--

BeFull is an alternative UI to the Deskbar for launching apps.

Why bother?
--

I think that a quick full-screen app that is efficiently keyboard- and mouse-accessible is the best way to launch programs.  Why only show part of your menu and have to wait, when you can show the whole thing and get what you want with one click or a couple keystrokes?

How do I use it?
--
1.  Launch BeFull.
2.  Click to launch an item and quit BeFull at the same time.

What other cool features does it have?
--
You can use something other than /boot/home/config/be as your menu, and you can attach specific colours to any folder.  If you colour one folder but not its sub-folders, the subfolders alternate using the parent folder's colour and a lighter variation of it.

The menu resizes itself to fit whatever you have in your menu--any extra space due to rounding errors is filled in with extra button.  (You'll probably notice that the buttons along the bottom are a little bigger than the rest, and sometimes the ones in the rightmost column are too.)

The rightmost column is 30% skinnier than other columns, because you can get your mouse lined up with it the quickest (dart right).  

Button labels are resized or chopped if need be to fit into their buttons.

Be menu folders are recursively displayed.  Don't link to a folder with a bajillion files in it, or you may have to wait awhile.

Groups are (gasp!) labeled.

Right now, you can quit without opening any apps by switching workspaces or pressing any key (at some point this will be narrowed down to the escape key.)

Broken symlinks are now indicated as such ("toast").

How do I edit the settings file, and why is the link broken?
--
You have to run the program once for the link to work.  What happens is, if there's no settings file at "/boot/home/config/settings/BeFull Settings", it makes one using ls.  If there is one, it'll overwrite it every time unless you add a blank line at the beginning.  So if you want random colours and a menu that always mirrors your Be menu, don't touch anything.

If you want a different menu displayed than the Be menu, go to a Terminal and type, `ls -L -1 -R menulocation > /boot/home/config/settings/BeFull\ Settings`, where menulocation is wherever your desired menu is located, with any spaces preceeded by a backslash, as always.  Then open the file using the link, add a blank line at the start, and save it.

If you want your own colours and/or a static menu, add the blank line, and a colour right after the colon (":") after any folder name.  Each colour will be applied to the group and variations of it to any subgroups it may have.  Wherever there isn't a colour, BeFull will generate one.  Make sure your colours are in the format "R G B", where each red, green, or blue value is an integer from 0 to 210 inclusive (higher than that and it'll be chopped automatically--you can't see it well with the white font face, and boosted subfolder variations would be worse.)  The highlight and text colours are always the same--I decided this was the easiest way to do things.

Todo list for source adopters:
--
1. One user has reported graphic corruption problems, but I couldn't determine the cause.
2. Replicant edition source is lost.  (Binary is included here.)  It was only a few lines different IIRC.
3. I remember someone saying that the first run load time is a bit scary because of the screen going blank during loading.  That could definitely be avoided.
4. Support for the keyboard (besides quitting), text-only mode, many options, and treating queries as folders.
5. The idea is someday there'll be a really quick way to launch BeFull from anywhere (single click, mouse gesture, or keyboard button, like perhaps a 104-key-keyboard special key.)  For now you can download SpicyKeys from BeBits, which works very well.  If you have a newer version of OpenDeskbar, the Be menu will still pop up in the background, but it doesn't really affect anything except that the mouse gets moved to the corner.
6. Provide a compiled binary and screenshot of 0.04 (non-replicant) too.

Here's what the non-fullscreen, Replicant Edition (0.05) looks like:

![Replicant Edition screenshot](https://raw.githubusercontent.com/KevinField/BeFull/master/BeFull_0.05.png)
