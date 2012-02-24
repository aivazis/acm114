<?xml version="1.0" encoding="utf-8"?>
<!--
!
! michael a.g. aïvázis
! california institute of technology
! (c) 1998-2012 all rights reserved
!
-->

<config>

  <!-- the application that grants access to student's homework -->
  <component name="access">
    <bind property="course">acm114</bind>
  </component>

  <!-- the application that identifies students with missing homework repositories -->
  <component name="hw-missing">
    <bind property="course">acm114</bind>
  </component>

  <!-- the application that posts homework assignments -->
  <component name="hw-post">
    <bind property="course">acm114</bind>
    <bind property="repository">bzr#bzr-acm114</bind>
  </component>

  <!-- the application that initializes the homework repositories -->
  <component name="init-repo">
    <bind property="course">acm114</bind>
    <bind property="repository">bzr#bzr-acm114</bind>
  </component>

  <!-- the application that initializes the project repositories -->
  <component name="project-init">
    <bind property="course">acm114</bind>
    <bind property="repository">bzr#bzr-acm114</bind>
  </component>

  <!-- the application that serves the student's homework repositories -->
  <component name="homework">
    <bind property="course">acm114</bind>
    <bind property="repository">bzr#bzr-acm114</bind>
  </component>


  <!-- the class -->
  <component family="syllabus.courses.acm114">
    <bind property="home">/home/projects/acm114/web</bind>
    <bind property="term">2012-winter</bind>
  </component>

  <!-- bzr on acm114.caltech.edu, an ubuntu 11.10 virtual machine -->
  <component name="bzr-acm114" family="syllabus.repositories.bzr">
    <bind property="executable">/usr/bin/bzr</bind>
    <bind property="write">yes</bind>
  </component>

  <!-- bzr on my macs -->
  <component name="bzr-macports" family="syllabus.repositories.bzr">
    <bind property="executable">/opt/local/bin/bzr</bind>
    <bind property="write">yes</bind>
  </component>

</config>


<!-- end of file -->
