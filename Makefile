all: ls rm

ls : ls.c
	gcc ls.c -o ls

rm : rm.c
	gcc rm.c -o rm

install : ls rm
	install ls ~/.local/bin
	install rm ~/.local/bin

uninstall:
	rm --force ~/.local/bin/ls
	rm --force ~/.local/bin/rm
