/*
 * lar - LinuxBIOS archiver
 *
 * Copyright (C) 2006-2007 coresystems GmbH
 * (Written by Stefan Reinauer <stepan@coresystems.de> for coresystems GmbH)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA, 02110-1301 USA
 */

#ifndef __LAR_LIB_H
#define __LAR_LIB_H

/* data types */

struct file {
	char *name;
	struct file *next;
};

enum {
	NONE,
	ADD,
	CREATE,
	LIST,
	EXTRACT
} larmodes;

/* prototypes for lar.c functions */
int verbose(void);
int elfparse(void);
long get_larsize(void);
char *get_bootblock(void);

/* prototypes for lib.c functions */
int mkdirp_below(const char *parent, const char *dirpath, mode_t mode);

int add_files(const char *name);
int add_file_or_directory(const char *name);

struct file *get_files(void);
void free_files(void);

/* Prototypes for ELF functions */
int iself(char *filebuf);

/* Prototypes for in-memory LAR operations */
int lar_process_name(char *name, char **pfilename, char **ppathname, 
		enum compalgo *thisalgo);
u32 lar_compress(char *ptr, ssize_t size, char *temp, enum compalgo *thisalgo);
int lar_add_entry(struct lar *lar, char *pathname, void *data, 
	u32 complen, u32 reallen, u32 loadaddress, u32 entry, 
	enum compalgo thisalgo);
/* Prototypes for the LAR I/O functions */
char *mapfile(char *filename, u32 *size);
struct lar * lar_new_archive(const char *archive, unsigned int size);
struct lar * lar_open_archive(const char *archive);
void lar_close_archive(struct lar *lar);

void lar_list_files(struct lar *lar, struct file *files);
int lar_add_file(struct lar *lar, char *name);
int lar_add_bootblock(struct lar *lar, const char *bootblock);
int lar_extract_files(struct lar *lar, struct file *files);

/* prototypes for extract.c functions */
int extract_lar(const char *archivename, struct file *files);

/* prototypes for list.c functions */
int list_lar(const char *archivename, struct file *files);

/* prototypes for create.c functions */
int create_lar(const char *archivename, struct file *files);

/* prototypes for bootblock.c functions */
extern char *bootblock_code;
extern int bootblock_len;

int load_bootblock(const char *bootblock);
int fixup_bootblock(void);
#endif
