import sys
import os
import subprocess

_version = sys.version_info[0];

class utils:
    class version:
        major = _version;
        info  = sys.version_info;
        full  = sys.version;
    class msg:
        attr  = {
            ""         : '',
            "end"      : '\033[0m',
            "bold"     : '\033[1m',
            "dark"     : '\033[2m',
            "italic"   : '\033[3m',
            "underline": '\033[4m',
            "blink"    : '\033[5m',
            "cross"    : '\033[9m' # tachar
        }
        highlight = {
            ""       : '',
            "red"    : '\033[41m',
            "green"  : '\033[42m',
            "orange" : '\033[43m',
            "blue"   : '\033[44m',
            "magenta": '\033[45m',
            "cyan"   : '\033[46m',
            "grey"   : '\033[47m'
        }
        color = {
            ""       : '',
            "red"    : '\033[31m',
            "green"  : '\033[32m',
            "orange" : '\033[33m',
            "blue"   : '\033[34m',
            "magenta": '\033[35m',
            "cyan"   : '\033[36m',
            "grey"   : '\033[37m'
        }
        @staticmethod
        def printm(message, color = '', highlight = '', attr = ''):
            print (utils.msg.color[color] + utils.msg.highlight[highlight] + utils.msg.attr[attr] + message + utils.msg.attr["end"]);
    class shell:
        devnull = open(os.devnull, 'w');
        stdio   = None;
        _stdout = None;
        _stderr = None;
        _stdin  = None;
        def __init__(self, stdin = None, stdout = None, stderr = None):
            self._stdout = stdout;
            self._stderr = stderr;
            self._stdin  = stdin;
        def setIO(self, stdin = "", stdout = "", stderr = ""):
            if(stdin != ""):
                self._stdin  = stdin;
            if(stdout != ""):
                self._stdout = stdout;
            if(stderr != ""):
                self._stderr = stderr;
        def run(self, cmd):
            subprocess.call(cmd.split(' '), stdin = self._stdin, stdout = self._stdout, stderr = self._stderr);
