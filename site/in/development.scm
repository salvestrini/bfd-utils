(h2 "DEVELOPMENT")

(h3 "Browsing sources")
(p "You can browse the "
   (a (@ (href "http://git.savannah.nongnu.org/gitweb/?p=dnt.git"))
      "Git repository")
   " of this project with your web browser. This gives you a good "
   "picture of the current status of the source files. You may also view "
   "the complete histories of any file in the repository as well as "
   "differences among two versions.")

(h3 "Getting a copy of the Git Repository")
(p "Anonymous checkout:")
(pre (@ class "terminal")
     (a (@ (href "http://savannah.gnu.org/maintenance/UsingGit")) "git")
     " clone git://git.savannah.nongnu.org/dnt.git")

(h3 "Bootstrapping the sources")
(p "Once you have the repository on your machine you should run the "
   "convenience script " (kbd "bootstrap") " located in the root directory. "
   "The script will look for the required tools and will (re)build "
   "some files. If everything works as supposed you will be able to "
   "configure the package using the " (kbd "configure") " script")

(h3 "Contribute")
(p "If you have time and programming skills, you can help us by developing "
   "missing features, regression tests or bug-fixing the present codebase. "
   "Subscribe to the "
   (a (@ (href "http://lists.nongnu.org/mailman/listinfo/dnt-generic"))
      "mailing list")
   ", drop us a mail and start coding. Send your code to the "
   "mailing list under the form of patches for the current revision system.")
(p "If you have time but no programming skills, you can help with "
   "documentation,  packaging, tests before releases etc ...")
