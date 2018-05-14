#!/bin/sh

#HOME is a predefined environment variable

JAVA_WRAPPERS=java-wrappers.tgz
DOT_ARCHIVE=cs181.files.tgz
DOT_FILES=".bashrc .bash_profile .emacs .screenrc .xinitrc"

# unpack ${JAVA_WRAPPERS} in ${HOME}/bin/ (subdir created if not present)
tar -xzvf ${JAVA_WRAPPERS} -C ${HOME}
# unpack ${DOT_ARCHIVE} in ${HOME}/.dot/ (subdir created if not present)
tar -xzvf ${DOT_ARCHIVE}   -C ${HOME}
# make few symlinks from ${HOME} into ${HOME}/.dot/
for i in ${DOT_FILES}; do
    echo "installing $i (original saved into ${HOME}/$i.orig if existant)"
    test -f ${HOME}/$i && cp -f ${HOME}/$i ${HOME}/$i.orig
    ln -fs ${HOME}/.dot/$i ${HOME}/
done
