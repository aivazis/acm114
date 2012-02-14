# -*- Makefile -*-
#
# michael a.g. aïvázis
# california institute of technology
# (c) 1998-2012 all rights reserved
#

PROJECT = acm114
PACKAGE = lectures

RECURSE_DIRS = \
   figures \
   listings \

OTHERS = \

#--------------------------------------------------------------------------
#

DOCUMENT = acm114

PACKAGES =

INCLUDES = \
    acm114.sty \
    setup.tex \
    references.bib

SECTIONS = \
    20120104.tex \
    20120106.tex \
    20120109.tex \
    20120111.tex \
    20120113.tex \
    20120120.tex \
    20120123.tex \
    20120125.tex \
    20120127.tex \
    20120130.tex \
    20120201.tex \
    20120203.tex \
    20120206.tex \
    20120208.tex \
    20120210.tex \
    20120213.tex \
    20120215.tex \

FIGURES = \
    figures/amdahl.pdf \
    figures/asymptotic-o.pdf \
    figures/asymptotic-omega.pdf \
    figures/asymptotic-theta.pdf \
    figures/dilog-quadrature.pdf \
    figures/distributed-memory.pdf \
    figures/generic-parallel-architecture.pdf \
    figures/laplace-example.pdf \
    figures/mpi-alltoall-pattern.pdf \
    figures/mpi-bcast-pattern.pdf \
    figures/mpi-data-patterns.pdf \
    figures/mpi-gather-pattern.pdf \
    figures/mpi-gather.pdf \
    figures/mpi-scatter-pattern.pdf \
    figures/mpi-scatter.pdf \
    figures/parallelization-steps.pdf \
    figures/putty-initial.png \
    figures/putty-key.png \
    figures/reduction-comsync-redundancy.pdf \
    figures/reduction-comsync-replication.pdf \
    figures/reduction-comsync.pdf \
    figures/reduction-distributed.pdf \
    figures/reduction-load-imbalance.pdf \
    figures/reduction-overhead.pdf \
    figures/reduction-parallel-work.pdf \
    figures/reduction-partial-sum.pdf \
    figures/reduction-partitioned-work.pdf \
    figures/reduction-shared.pdf \
    figures/reduction-simd.pdf \
    figures/reduction-tree-sum.pdf \
    figures/shared-memory.pdf \
    figures/simd.pdf \
    figures/structured.pdf \
    figures/structured-1d-centered.pdf \
    figures/structured-1d-left.pdf \
    figures/structured-1d-middle.pdf \
    figures/structured-1d-right.pdf \
    figures/structured-1d-5c.pdf \
    figures/structured-1d-51.pdf \
    figures/structured-1d-52.pdf \
    figures/structured-1d-54.pdf \
    figures/structured-1d-55.pdf \
    figures/structured-2d-average.pdf \
    figures/structured-2d-centered.pdf \
    figures/structured-2d-e.pdf \
    figures/structured-2d-middle.pdf \
    figures/structured-2d-n.pdf \
    figures/structured-2d-ne.pdf \
    figures/structured-2d-nw.pdf \
    figures/structured-2d-s.pdf \
    figures/structured-2d-se.pdf \
    figures/structured-2d-sw.pdf \
    figures/structured-2d-w.pdf \
    figures/structured-coordinates.pdf \
    figures/structured-dirichlet.pdf \
    figures/structured-partitioning.pdf \
    figures/structured-updates.pdf \
    figures/threads.pdf \
    figures/threads-memory.pdf \
    figures/threads-reduction.pdf \

#--------------------------------------------------------------------------
#

all: $(DOCUMENT).pdf

tidy::
	BLD_ACTION="tidy" $(MM) recurse

clean::
	BLD_ACTION="clean" $(MM) recurse

distclean::
	BLD_ACTION="distclean" $(MM) recurse


#--------------------------------------------------------------------------
#

# preview types
osx: $(DOCUMENT).pdf
	open -g $(DOCUMENT).pdf

xpdf: $(DOCUMENT).pdf
	xpdf -remote $(DOCUMENT) $(DOCUMENT).pdf

# make the document using the default document class
$(DOCUMENT).pdf: $(DOCUMENT).tex $(PACKAGES) $(INCLUDES) $(SECTIONS) $(FIGURES)

# housekeeping
PROJ_CLEAN += $(CLEAN_LATEX) *.snm *.nav *.vrb 
PROJ_DISTCLEAN += *.ps *.pdf $(PROJ_CLEAN)

# end of file
