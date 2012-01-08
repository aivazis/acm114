<?xml version="1.0" encoding="utf-8"?>
<!--
!
! michael a.g. aïvázis
! california institute of technology
! (c) 1998-2012 all rights reserved
!
-->

<config>

  <!-- the homework app -->
  <component name="homework">
    <bind property="course">acm114</bind>
    <bind property="repository">bzr#bzr-ubuntu</bind>
  </component>

  <!-- the class -->
  <component family="syllabus.courses.acm114">
    <bind property="home">/home/projects/acm114/web</bind>
    <bind property="term">2012-winter</bind>
  </component>

  <!-- bzr on macports -->
  <component name="bzr-macports" family="syllabus.repositories.bzr">
    <bind property="executable">/opt/local/bin/bzr</bind>
  </component>

  <!-- bzr on ubuntu -->
  <component name="bzr-ubuntu" family="syllabus.repositories.bzr">
    <bind property="executable">/usr/bin/bzr</bind>
  </component>

</config>


<!-- end of file -->
