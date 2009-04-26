(h2 "INSTALLATION")

(h3 "Prerequisites")
(p "In order to install the package into your system "
   "you will need:"
   (ul
    (li (a (@ (href "http://www.python.org")) "Python > 2.5") )
    )
   )

(h3 "Installation")
(p "The following notes do not override your system's package management "
   "software, please follow your system's guidelines to install the software.")

(p ,as_site_variable_PROGRAMNAME " uses the "
   (a (@ (href "http://en.wikipedia.org/wiki/Autotools")) autotools)
   " facilities, the simplest way to install the package in your system is:")

(ul
 (li (kbd "cd") " to the directory containing the package's source code "
     "and type " (kbd "./configure") " to configure the package for your "
     "system."
     "Running " (kbd "configure") " might take a while. While running, "
     "it prints some messages telling which features it is checking for")
 (li "Type " (kbd "make") " to compile the package")
 (li "Optionally, type " (kbd "make check") " to run all self-tests that "
     "come with the package")
 (li "Type " (kbd "make install") " to install the programs and any data "
     "files and documentation"))

(p "Use " (kbd "./configure --help") " to get a brief help of all "
   "configuration tweaks available.")
(p "You can remove the program binaries and object files from the "
   "source code directory by typing " (kbd "make clean") ". "
   "To also remove the files that " (samp "configure") " created (so you "
   "can compile the package for a different architecture), type "
   (kbd "make distclean") ".")
(p "You can also type " (kbd "make uninstall") " to remove the installed "
   "files.")
(p "Note that the " (samp "--prefix") " option allows installation using "
   "different paths than the default ones, this option enables sandbox "
   "installations.")
