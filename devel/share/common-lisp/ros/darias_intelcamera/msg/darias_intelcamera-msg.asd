
(cl:in-package :asdf)

(defsystem "darias_intelcamera-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "maplist" :depends-on ("_package_maplist"))
    (:file "_package_maplist" :depends-on ("_package"))
  ))