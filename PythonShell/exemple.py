from utils import *

gitURL    = "https://github.com/geoffreytran/AX88179_178A.git";
gitFolder = "AX88179_178A";

sh = utils.shell();
# supress stdout
sh.setIO(stdout = sh.devnull);

printm = utils.msg.printm;

printm("Cloning git repo...", "green");
sh.run("git clone " + gitURL);

printm("Building archives...", "green");
sh.run("sudo make --directory=" + gitFolder);
sh.run("sudo make install --directory=" + gitFolder);

printm("Done.", "green");

printm("Loading Driver...", "green");
sh.run("sudo modprobe usbnet");
sh.run("sudo insmod ax88179_178a.ko");
