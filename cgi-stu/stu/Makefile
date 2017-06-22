CC=gcc
AFLAGS=-Wall -g
LDFLAGS= -lmysqlclient
OBJS= add.cgi del.cgi mod.cgi sel.cgi add_score.cgi score_sel.cgi fakedel.cgi recover.cgi class_mod.cgi add_class.cgi class_sel.cgi score_del.cgi  class_del.cgi

all:$(OBJS)

$(OBJS):%.cgi:%.c
	$(CC) $(AFLAGS) $< cgic.c -o $@ $(LDFLAGS)

.PHONY:clean
clean:
	rm ./*.cgi

install:
	cp *.cgi /usr/lib/cgi-bin/sx/
	cp head.html footer.html /usr/lib/cgi-bin/sx/
	sudo cp -r public/ index.html student.html teacher.html /var/www/html/
