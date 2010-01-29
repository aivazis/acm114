# -*- Makefile -*-
#
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#
#                             michael a.g. aïvázis
#                      california institute of technology
#                      (c) 1998-2010  all rights reserved
#
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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
    20100104.tex \
    20100106.tex \
    20100108.tex \
    20100111.tex \
    20100113.tex \
    20100115.tex \
    20100120.tex \
    20100122.tex \
    20100125.tex \
    20100127.tex \
    20100129.tex \
    sandbox.tex \

FIGURES = \
    figures/amdahl.pdf \
    figures/asymptotic-o.pdf \
    figures/asymptotic-omega.pdf \
    figures/asymptotic-theta.pdf \
    figures/cuda-architecture.pdf \
    figures/cuda-blocks.pdf \
    figures/distributed-memory.pdf \
    figures/generic-parallel-architecture.pdf \
    figures/mpi-bcast-pattern.pdf \
    figures/mpi-data-patterns.pdf \
    figures/mpi-gather.pdf \
    figures/mpi-gather-pattern.pdf \
    figures/mpi-scatter.pdf \
    figures/mpi-scatter-pattern.pdf \
    figures/parallelization-steps.pdf \
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
    figures/threads-memory.pdf \
    figures/threads-reduction.pdf \
    figures/threads.pdf \

#--------------------------------------------------------------------------
#

all: $(DOCUMENT).pdf
	BLD_ACTION="all" $(MM) recurse

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
	open $(DOCUMENT).pdf

xpdf: $(DOCUMENT).pdf
	xpdf -remote $(DOCUMENT) $(DOCUMENT).pdf

# make the document using the default document class
$(DOCUMENT).pdf: $(DOCUMENT).tex $(PACKAGES) $(INCLUDES) $(SECTIONS) $(FIGURES)

# housekeeping
PROJ_CLEAN = $(CLEAN_LATEX) *.snm *.nav *.vrb 
PROJ_DISTCLEAN = *.ps *.pdf $(PROJ_CLEAN)

# end of file
