all: ls rm cat sleep

ls : ls.c
	gcc ls.c -o ls

rm : rm.c
	gcc rm.c -o rm

cat : cat.c
	gcc cat.c -o cat

sleep : sleep.c
	gcc sleep.c -o sleep

install : ls rm
	install ls ~/.local/bin
	install rm ~/.local/bin
	install cat ~/.local/bin
	install sleep ~/.local/bin

uninstall:
	rm --force ~/.local/bin/rm
	rm --force ~/.local/bin/ls
	rm --force ~/.local/bin/cat
	rm --force ~/.local/bin/sleep
