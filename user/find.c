#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"
char * fmtname(char *);
char * fmtname(char *path)
{
	static char buf[DIRSIZ + 1];
	char *p;;

	for (p = path + strlen(path); p >= path && *p != '/'; p--);
	p++;

	if (strlen(p) >= DIRSIZ)
		return p;
	
	memmove(buf, p, strlen(p));
	memset(buf + strlen(p), ' ', DIRSIZ - strlen(p));

	return buf;
}
void find(char *path, char *file)
{
	char buf[512], *p;
	//char filename[128] = {};
	int fd;
	struct dirent de;
	struct stat st;

	if ((fd = open(path, O_RDONLY)) < 0) {
		fprintf(2, "find: cannot open %s\n", path);
		return;
	}

	if (fstat(fd, &st) < 0) {
		fprintf(2, "find: cannot stat %s\n", path);
		close(fd);
		return;
	}

	switch (st.type) {
	case T_DEVICE:
	case T_FILE:
		//strcpy(file, fmtname(path));
		//only once when the cmd is find file1 file2.
		printf("Usage: find [path] [file]\n");
		break;
	
	case T_DIR:
		if (strlen(path) + 1 + DIRSIZ + 1 > sizeof buf) {
			printf("find: path too long\n");
			break;
		}
		strcpy(buf, path);
		p = buf + strlen(buf);
		*p++ = '/';
		while (read(fd, &de, sizeof(de)) == sizeof(de)) {
			//Watch out FAT FINGER!
			if (strcmp(de.name, ".") == 0 || \
					strcmp(de.name, "..") == 0) {
				continue;
			}
			if (de.inum == 0)
					continue;
			memmove(p, de.name, DIRSIZ); // construct the next dir
			p[DIRSIZ] = 0;
			//printf("find: p:%s\n", p);
			if (stat(buf, &st) < 0) {
				printf("find: cannot stat %s\n", buf);
				continue;
			}
			
			
			if (st.type == T_DEVICE || st.type == T_FILE)
			{
				if (strcmp(p, file) == 0)
					printf("%s\n", buf);
				continue;
			}
			find(buf, file);
		}
		break;
	}
	close(fd);
}
int main(int argc, char* argv[])
{
	if (argc != 3) {
		fprintf(2, "Usage: find [root dir] [file name]\n");
		exit(0);
	}

	find(argv[1], argv[2]);
	exit(0);	
}
