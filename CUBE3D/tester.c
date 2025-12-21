#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/extensions/XTest.h>
#include <dirent.h>
#include <string.h>
#include <limits.h>
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define BLUE "\033[0;34m"
# define RESET "\033[0m"

#define WAIT_BEFORE_ESC 3

void	send_esc_key(void)
{
	Display	*display;
	KeyCode	esc;

	display = XOpenDisplay(NULL);
	if (!display)
	{
		fprintf(stderr, "Error: cannot open X display\n");
		return;
	}

	esc = XKeysymToKeycode(display, XK_Escape);

	XTestFakeKeyEvent(display, esc, True, CurrentTime);
	XTestFakeKeyEvent(display, esc, False, CurrentTime);

	XFlush(display);
	XCloseDisplay(display);
}

int	run_map(char *cub3d_path, char *map_path)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		execl(cub3d_path, cub3d_path, map_path, NULL);
		perror("exec");
		exit(1);
	}

	sleep(WAIT_BEFORE_ESC);
	send_esc_key();

	waitpid(pid, &status, 0);

	if (WIFSIGNALED(status))
	{
		int sig = WTERMSIG(status);

		if (sig == SIGSEGV)
			printf(RED"Segmentation fault detected\n"RESET);
		else
			printf(RED"Crashed with signal %d\n"RESET, sig);
	}
	else if (WIFEXITED(status))
	{
		int code = WEXITSTATUS(status);
		printf(GREEN"Exited normally (code %d)\n"RESET, code);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	DIR				*dir;
	struct dirent	*entry;
	char			path[PATH_MAX];
	char			*cub3d = "./cub3d";
	char			*map_dir = "maps";

	(void)argc;
	(void)argv;

	dir = opendir(map_dir);
	if (!dir)
		return (perror("opendir"), 1);

	while ((entry = readdir(dir)))
	{

		snprintf(path, sizeof(path), "%s/%s",
			map_dir, entry->d_name);

		printf("\n▶ Testing %s\n", path);
		run_map(cub3d, path);
		sleep(1);
	}

	closedir(dir);
	printf("\nAll maps tested.\n");
	return (0);
}

