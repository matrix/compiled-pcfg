//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Pretty Cool Fuzzy Guesser (PCFG)
//  --Probabilistic Context Free Grammar (PCFG) Password Guessing Program
//
//  Written by Matt Weir
//  Special thanks to the John the Ripper and Hashcat communities where some 
//  of the code was copied from. And thank you whoever is reading this. Be good!
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//
//

#include "command_line.h"

static void usage(const char *progname) {
    printf("Usage: %s [OPTION...] ARG1 ARG2\n", progname);
    printf("Pretty Cool Fuzzy Guesser: Version %s\n\n", VERSION);
    printf("  -d, --debug                Prints out debugging info vs guesses.\n");
    printf("  -r, --rule_name=OUTFILE    The ruleset to use. Default is: 'Default'\n");
    printf("  -?, --help                 Give this help list\n");
    printf("  -V, --version              Print program version\n\n");
    printf("Mandatory or optional arguments to long options are also mandatory or optional\n");
    printf("for any corresponding short options.\n\n");
    printf("A program for generationg password guesses\n");
}

int parse_command_line(int argc, char **argv, struct program_info *program_info) {
    // Set defaults
    program_info->rule_name = "Default";
    program_info->debug = 0;
    program_info->version = VERSION;
    program_info->min_supported_version = MIN_SUPPORTED_VERSION;

    // Define long options equivalent to your argp table
    static struct option long_options[] = {
        {"debug",     no_argument,       0, 'd'},
        {"rule_name", required_argument, 0, 'r'},
        {"help",      no_argument,       0, '?'},
        {"version",   no_argument,       0, 'V'},
        {0, 0, 0, 0}
    };

    int opt;
    while ((opt = getopt_long(argc, argv, "dr:?uV", long_options, NULL)) != -1) {
        switch (opt) {
            case 'd':
                program_info->debug = 1;
                break;
            case 'r':
                program_info->rule_name = strdup(optarg);
                break;
            case 'V':
                printf("%s\n", VERSION);
                exit(0);
            case '?':
            default:
                usage(argv[0]);
                exit(0);
        }
    }

    return 0;
}
