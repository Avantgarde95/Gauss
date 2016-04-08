# ----- parameters -----

# =============================
# === modify this part only ===
# =============================

TARGETDIR = bin
OBJDIR = obj

SRCS1 = gauss_seq.c
SRCS2 = gauss_pth.c
SRCS3 = gauss_omp.c

TARGET1 = gauss_seq
TARGET2 = gauss_pth
TARGET3 = gauss_omp

# =============================

# ----- parameters_auto -----

OBJS1 = $(patsubst %.c, %.o, $(SRCS1))
OBJS2 = $(patsubst %.c, %.o, $(SRCS2))
OBJS3 = $(patsubst %.c, %.o, $(SRCS3))

# ----- compiler -----

CC = gcc
CFLAGS = -O2 -g -Wall
LDFLAGS = -lm

# ----- build rules -----

all : makedir target_1 target_2 target_3

makedir :
	mkdir -p $(OBJDIR) && mkdir -p $(TARGETDIR)

target_1 :
	cd $(OBJDIR) &&\
	$(CC) $(CFLAGS) -c ../$(SRCS1) &&\
	$(CC) $(CFLAGS) -o ../$(TARGETDIR)/$(TARGET1)\
       		$(OBJS1) $(LDFLAGS) &&\
	cd ..

target_2 :
	cd $(OBJDIR) &&\
	$(CC) $(CFLAGS) -c ../$(SRCS2) &&\
	$(CC) $(CFLAGS) -o ../$(TARGETDIR)/$(TARGET2)\
       		$(OBJS2) $(LDFLAGS) -lpthread &&\
	cd ..

target_3 :
	cd $(OBJDIR) &&\
	$(CC) $(CFLAGS) -c ../$(SRCS3) -fopenmp &&\
	$(CC) $(CFLAGS) -o ../$(TARGETDIR)/$(TARGET3)\
       		$(OBJS3) $(LDFLAGS) -fopenmp &&\
	cd ..

# ----- clean rules -----

clean :
	rm -rf $(OBJDIR) && rm -rf $(TARGETDIR)

