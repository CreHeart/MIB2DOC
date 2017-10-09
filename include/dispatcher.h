#ifndef _DISPATCHER_H_
#define _DISPATCHER_H_

#include "type.h"
#include "stack.h"

typedef enum dispatch_type {
    DISPATCH_PARAM_STAGE = 0,
    MIBTREE_GENERATION,
    SYMBOL_COLLECTING,
    SWITCH_TO_INC_BUFFER,
    IGNORE
} dispatch_type;

typedef enum dispatch_mode {
    DISPATCH_MODE_SYMBOL_COLLECTING = 0,
    DISPATCH_MODE_DOC_GENERATING = 1
} dispatch_mode;

typedef struct identList {
    int found;
    char *symName;
    listNode *next;
} identList;

struct yy_buffer_state {
	FILE *yy_input_file;

	char *yy_ch_buf;		/* input buffer */
	char *yy_buf_pos;		/* current position in input buffer */

	/* Size of input buffer in bytes, not including room for EOB
	 * characters.
	 */
	int yy_buf_size;

	/* Number of characters read into yy_ch_buf, not including EOB
	 * characters.
	 */
	int yy_n_chars;

	/* Whether we "own" the buffer - i.e., we know we created it,
	 * and can realloc() it to grow it, and should free() it to
	 * delete it.
	 */
	int yy_is_our_buffer;

	/* Whether this is an "interactive" input source; if so, and
	 * if we're using stdio for input, then we want to use getc()
	 * instead of fread(), to make sure we stop fetching input after
	 * each newline.
	 */
	int yy_is_interactive;

	/* Whether we're considered to be at the beginning of a line.
	 * If so, '^' rules will be active on the next match, otherwise
	 * not.
	 */
	int yy_at_bol;

    int yy_bs_lineno; /**< The line count. */
    int yy_bs_column; /**< The column count. */

	/* Whether to try to fill the input buffer when we reach the
	 * end of it.
	 */
	int yy_fill_buffer;

	int yy_buffer_status;

#define YY_BUFFER_NEW 0
#define YY_BUFFER_NORMAL 1
	/* When an EOF's been seen but there's still some text to process
	 * then we mark the buffer as YY_EOF_PENDING, to indicate that we
	 * shouldn't try reading from the input source any more.  We might
	 * still have a bunch of tokens to match, though, because of
	 * possible backing-up.
	 *
	 * When we actually see the EOF, we change the status to "new"
	 * (via yyrestart()), so that the user can continue scanning by
	 * just pointing yyin at a new input file.
	 */
#define YY_BUFFER_EOF_PENDING {

};

typedef struct yy_buffer_state * YY_BUFFER_STATE;

typedef struct collectInfo {
    char *modName;
    identList *symbols;
} collectInfo;

#define MAX_INCLUDE_DEPTH 10
typedef struct switchingState {
    /* Include status or Non-Include status */
    int state;
    /* Number of modules in stack */
    int counter;
    /* Stack of struct collectInfo */
    genericStack *modStack;
    /* Buffer stack */
    YY_BUFFER_STATE importStack[MAX_INCLUDE_DEPTH];
    int importStackIndex;
} switchingState;


YY_BUFFER_STATE * getCurrentBufferState();
errorType dispatch(dispatch_type dType, params_t * param);

#endif /* _DISPATCHER_H_ */
