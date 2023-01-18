APPNAME = wamon
CFLAGS = -O3 -fcommon

OBJS = 		main.o 		\
		ds.o 		\
		iface.o		\
		list.o 		\
		item.o 		\
		tiempo.o

%.o: 		%.c
		$(CC) -c $< -o $@ $(CFLAGS)

$(APPNAME):	$(OBJS)
		$(CC) $(OBJS) -o $(APPNAME) $(CFLAGS)

all:		$(APPNAME)

clean:
		rm $(OBJS) $(APPNAME)

