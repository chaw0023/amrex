AMREX_INSTALL_DIR = ~/Softwares/amrex/build
DIM = 3
USE_MPI = TRUE
USE_OMP = FALSE
COMP = gnu
DEBUG = FALSE
USE_PARTICLES = TRUE
USE_FORTRAN_INTERFACE = TRUE
USE_LINEAR_SOLVERS = TRUE
ALLOW_DIFFERENT_COMP = FALSE


AMREX_HOME := $(shell pwd)

include $(AMREX_HOME)/Tools/GNUMake/Make.defs

Pdirs := Base AmrCore Amr Boundary
ifeq ($(USE_PARTICLES),TRUE)
    Pdirs += Particle
endif
ifeq ($(USE_FORTRAN_INTERFACE),TRUE)
    Pdirs += F_Interfaces/Base F_Interfaces/Octree F_Interfaces/AmrCore
endif
ifeq ($(USE_LINEAR_SOLVERS),TRUE)
   Pdirs += LinearSolvers/MLMG LinearSolvers/C_CellMG LinearSolvers/C_to_F_MG
endif
Pdirs += F_Interfaces/LinearSolvers
Ppack := $(foreach dir, $(Pdirs), $(AMREX_HOME)/Src/$(dir)/Make.package)
include $(Ppack)

ifeq ($(USE_LINEAR_SOLVERS),TRUE)
    include $(AMREX_HOME)/Src/LinearSolvers/F_MG/FParallelMG.mak
    include $(AMREX_HOME)/Src/F_BaseLib/FParallelMG.mak
endif

all: $(amrexlib)
	@echo SUCCESS

.PHONY: distclean install uninstall

distclean: realclean
	$(SILENT) $(RM) GNUmakefile

install: install_lib install_headers install_fortran_modules

uninstall:
	@echo Uninstalling...
	$(SILENT) $(RM) -r $(AMREX_INSTALL_DIR)

include $(AMREX_HOME)/Tools/GNUMake/Make.rules
