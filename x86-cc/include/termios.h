#ifndef BLACKJACK_TERMIOS_H
#define BLACKJACK_TERMIOS_H

/* Blackjack does not yet expose POSIX terminal-control attributes.
 * This header intentionally advertises no tc* interfaces.  Programs
 * that only conditionally use termios can select their fallback path.
 */

#endif
