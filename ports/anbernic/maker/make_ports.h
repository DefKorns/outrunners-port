/**
 *    Name:        make_ports.h
 *    Description: OutRunners Anbernic's work, for its command line and its window alike: the folder PORTS for
 *                 the handheld's card from its inputs, their defaults, and what the window shows of each
 *    Version:     0.2.0
 *    Created:     30-10-2026
 *    Modified:    15-11-2026
 *    Author:      Sebastian Toyos
 *
 *    license:BSD-3-Clause
 *    Paths are as the C library's fopen takes them (on Windows, in the system's code page). The same tool
 *    built with ORUNNERS_R36S_MAKER is OutRunners R36S: the folder ports for the R36S's card (ArkOS), of the
 *    game's R36S build (ports/r36s); the names below are each one's.
 */
#ifndef ORUNNERS_ANBERNIC_MAKE_PORTS_H
#define ORUNNERS_ANBERNIC_MAKE_PORTS_H

#include <stddef.h>
#include <stdio.h>

#define PORTS_PATH_SIZE 1100

/* The tool's device: its name, the handheld's, the game's build beside it (its folder, what it is called, and
   the room after its option in the usage), the folder made and where it goes on the card */
#ifdef ORUNNERS_R36S_MAKER
#define PORTS_TOOL      "OutRunners R36S"
#define PORTS_HANDHELD  "the R36S on ArkOS"
#define PORTS_BUILD     "r36s"
#define PORTS_BUILD_OF  "R36S"
#define PORTS_BUILD_PAD "    "
#define PORTS_FOLDER    "ports"       /* (ArkOS's, at the top of the card's EASYROMS) */
#define PORTS_CARD      "EASYROMS"
#else
#define PORTS_TOOL      "OutRunners Anbernic"
#define PORTS_HANDHELD  "Anbernic's H700 handhelds"
#define PORTS_BUILD     "anbernic"
#define PORTS_BUILD_OF  "Anbernic"
#define PORTS_BUILD_PAD ""
#define PORTS_FOLDER    "PORTS"       /* (the stock firmware's, in the card's Roms) */
#define PORTS_CARD      "Roms"
#endif

/* What PORTS is made of, and where it goes */
typedef struct
{
	char rom[PORTS_PATH_SIZE];      /* the arcade ROM set: orunners.zip, or a folder of its files */
	char build[PORTS_PATH_SIZE];    /* the game's Anbernic build: OutRunners.sh, outrunners/OutRunners and
	                                   outrunners/input_prompts.bmp */
	char out[PORTS_PATH_SIZE];      /* the folder PORTS goes in, with its separator: the card's Roms, or any */
} ports_inputs;

/* How making it went */
typedef struct
{
	char what[80];                  /* what failed */
	char detail[PORTS_PATH_SIZE + 128];    /* what it failed on (a file, or what the part that failed tells), or "" */
	size_t size;                    /* the assets pack's bytes, when PORTS is written */
} ports_outcome;

/* Told the step making PORTS is at, a name of its own ("taking the assets out of the ROM set") */
typedef void (*ports_step)(void *context, const char *step);

/* A file dropped on the tool: the ROM set (orunners.zip, or a folder of its files) */
void ports_take_dropped(ports_inputs *inputs, const char *path);

/* The inputs not given, beside the tool (in the folder 'here', with its separator): orunners.zip, the folder
   anbernic (r36s), and PORTS beside it */
void ports_defaults(ports_inputs *inputs, const char *here);

/* PORTS in the folder 'out': true when it is written. Each step's lines go to 'log' (the command line's)
   unless it is NULL; 'step' (or NULL) is told each step as it starts. What failed is in 'outcome' */
int make_ports(const ports_inputs *inputs, FILE *log, ports_step step, void *context, ports_outcome *outcome);

/* The folder of a path, with its separator: "" for a bare name */
void ports_folder_of(const char *path, char *folder, size_t size);

/* What the window shows of each input */
int ports_file_exists(const char *path);
int ports_folder_exists(const char *path);
const char *ports_build_problem(const char *build);    /* NULL when the game's build is whole, else what is not */

#endif
