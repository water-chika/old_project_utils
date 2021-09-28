DESTDIR=
PREFIX=~/.local/bin
program=ls rm cat sleep mkdir chroot pwd cp echo
all: ${program}

ls : ls.c
	gcc ls.c -o ls

rm : rm.c
	gcc rm.c -o rm

cat : cat.c
	gcc cat.c -o cat

sleep : sleep.c
	gcc sleep.c -o sleep

clean:
	for prog in ${program}; do \
		rm --force $$prog; \
	done

install : all
	for prog in ${program}; do \
		install $$prog ${DESTDIR}${PREFIX}; \
	done

uninstall:
	for prog in ${program}; do \
		rm --force ~/.local/bin/$$prog; \
	done
