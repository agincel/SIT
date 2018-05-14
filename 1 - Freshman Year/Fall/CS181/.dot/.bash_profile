# base-files version 3.7-1

# To pick up the latest recommended .bash_profile content,
# look in /etc/defaults/etc/skel/.bash_profile

# Modifying /etc/skel/.bash_profile directly will prevent
# setup from updating it.

# The copy in your home directory (~/.bash_profile) is yours, please
# feel free to customise it to create a shell
# environment to your liking.  If you feel a change
# would be benifitial to all, please feel free to send
# a patch to the cygwin mailing list.

# ~/.bash_profile: executed by bash for login shells.

# source the system wide bashrc if it exists
if [ -e /etc/bash.bashrc ] ; then
  source /etc/bash.bashrc
fi

# source the users bashrc if it exists
if [ -e "${HOME}/.bashrc" ] ; then
  source "${HOME}/.bashrc"
fi

# Set PATH so it includes user's private bin if it exists
if [ -d "${HOME}/bin" ] ; then
  PATH=${HOME}/bin:${PATH}
fi

# Set MANPATH so it includes users' private man if it exists
# if [ -d "${HOME}/man" ]; then
#   MANPATH=${HOME}/man:${MANPATH}
# fi

# Set INFOPATH so it includes users' private info if it exists
# if [ -d "${HOME}/info" ]; then
#   INFOPATH=${HOME}/info:${INFOPATH}
# fi

####
#
# Antonio Nicolosi, CS181 
#
#   Setup environment variables so that Cygwin can find the JDK
#   installed under Windows.
#
#   Notes:
#
#   * If your JDK is not 1.7 update 5, or if it is not located 
#     within the "Program Files (x86)" folder, change JAVA_HOME
#     accordingly.
#   * RTJAR is setup assuming that your JRE is in a subdirectory
#     of the JDK install location.  Some installation instead have 
#     the JRE in a sibling folder to the JDK; if that's your case, 
#     change RTJAR accordingly.
#   * JAVASRC_HOME point to the folder with your Java programs.
#     We recommend that you create (mkdir) folders ~/cs181/ and 
#     ~/cs181/java/ in your cygwin home directory.  If you prefer
#     to place them in a different place, change JAVASRC_HOME.
#
####
export JAVA_HOME="/cygdrive/c/Program Files (x86)/Java/jdk1.7.0_05"
export RTJAR=${JAVA_HOME}/jre/lib/rt.jar
export JAVASRC_HOME=${HOME}/cs181/java/
export CLASSPATH=${JAVASRC_HOME}:${JAVASRC_HOME}/lib:${CLASSPATH}
