<?xml version="1.0" encoding="utf-8"?>
<!--
!
! michael a.g. aïvázis
! california institute of technology
! (c) 1998-2012 all rights reserved
!
-->

<config>

  <!-- this class -->
  <component name="acm114" family="syllabus.course">
    <bind property="server">import:syllabus.bzr#bzr-acm114</bind>
  </component>

  <!-- bzr on acm114.caltech.edu, an ubuntu 11.10 virtual machine -->
  <component name="bzr-acm114" family="syllabus.repositories.bzr">
    <bind property="executable">/usr/bin/bzr</bind>
    <bind property="write">yes</bind>
  </component>

</config>


<!-- end of file -->
