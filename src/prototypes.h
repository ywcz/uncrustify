/**
 * @file prototypes.h
 * Big jumble of prototypes used in Uncrustify.
 *
 * @author  Ben Gardner
 * @license GPL v2+
 *
 * $Id$
 */
#ifndef C_PARSE_PROTOTYPES_H_INCLUDED
#define C_PARSE_PROTOTYPES_H_INCLUDED

#include "uncrustify_types.h"

#include <string>

/*
 *  uncrustify.cpp
 */

const char *get_token_name(c_token_t token);
void log_pcf_flags(log_sev_t sev, UINT32 flags);
const char *path_basename(const char *path);
const char *get_file_extension(int &idx);


/*
 *  output.cpp
 */

void output_text(FILE *pfile);
void output_parsed(FILE *pfile);
void output_comment_multi(chunk_t *pc);
chunk_t *output_comment_cpp(chunk_t *pc);
void output_options(FILE *pfile);
void output_to_column(int column, bool allow_tabs);
void add_text(const char *text);
void add_text_len(const char *text, int len);
void add_char(char ch);


/*
 *  options.cpp
 */

void unc_begin_group(uncrustify_groups id, const char *short_desc, const char *long_desc = NULL);
void register_options(void);
void set_option_defaults(void);
int load_option_file(const char *filename);
int save_option_file(FILE *pfile, bool withDoc);
int set_option_value(const char *name, const char *value);
const group_map_value *get_group_name(int ug);
const option_map_value *get_option_name(int uo);
void print_options(FILE *pfile, bool verbose);

std::string argtype_to_string(argtype_e argtype);
std::string bool_to_string(bool val);
std::string argval_to_string(argval_t argval);
std::string number_to_string(int number);
std::string lineends_to_string(lineends_e linends);
std::string tokenpos_to_string(tokenpos_e tokenpos);
std::string op_val_to_string(argtype_e argtype, op_val_t op_val);

/*
 *  indent.cpp
 */

void indent_text(void);
void indent_preproc(void);
void indent_to_column(chunk_t *pc, int column);
void reindent_line(chunk_t *pc, int column);


/*
 *  align.cpp
 */

void align_all(void);
void align_backslash_newline(void);
void align_right_comments(void);
void align_func_proto(int span);
void align_preprocessor(void);
void align_struct_initializers(void);
chunk_t *align_nl_cont(chunk_t *start);
chunk_t *align_assign(chunk_t *first, int span, int thresh);


/*
 *  braces.cpp
 */

void do_braces(void);


/*
 *  parens.cpp
 */

void do_parens(void);


/*
 *  space.cpp
 */

void space_text(void);
void space_text_balance_nested_parens(void);
int space_col_align(chunk_t *first, chunk_t *second);
argval_t do_space(chunk_t *first, chunk_t *second);

void space_add_after(chunk_t *pc, int count);


/*
 *  combine.cpp
 */

void fix_symbols(void);
void combine_labels(void);
void mark_comments(void);
void make_type(chunk_t *pc);


/*
 *  newlines.cpp
 */

void newlines_cleanup_braces(void);
void newlines_insert_blank_lines(void);
void newlines_squeeze_ifdef(void);
void newlines_eat_start_end(void);
void newlines_bool_pos(void);
void newlines_class_colon_pos(void);
void newlines_cleanup_dup(void);
void newlines_double_space_struct_enum_union(void);
void do_blank_lines(void);
chunk_t *newline_add_before(chunk_t *pc);
chunk_t *newline_add_after(chunk_t *pc);


/*
 *  tokenize.cpp
 */

void tokenize(const char *data, int data_len);


/*
 *  tokenize_cleanup.cpp
 */

void tokenize_cleanup(void);


/*
 *  brace_cleanup.cpp
 */

void brace_cleanup(void);


/*
 *  keywords.cpp
 */

int load_keyword_file(const char *filename);
const chunk_tag_t *find_keyword(const char *word, int len);
void add_keyword(const char *tag, c_token_t type, UINT8 lang_flags);
void output_types(FILE *pfile);
const chunk_tag_t *get_custom_keyword_idx(int &idx);
void clear_keyword_file(void);
pattern_class get_token_pattern_class(c_token_t tok);


/*
 *  defines.cpp
 */

int load_define_file(const char *filename);
const define_tag_t *find_define(const char *word, int len);
void add_define(const char *tag, const char *value);
const define_tag_t *get_define_idx(int &idx);
void output_defines(FILE *pfile);
void clear_defines(void);


/*
 *  punctuators.cpp
 */
const chunk_tag_t *find_punctuator(const char *str, UINT8 lang_flags);


/*
 *  parse_frame.cpp
 */

void pf_copy(struct parse_frame *dst, const struct parse_frame *src);
void pf_push(struct parse_frame *pf);
void pf_push_under(struct parse_frame *pf);
void pf_copy_tos(struct parse_frame *pf);
void pf_trash_tos(void);
void pf_pop(struct parse_frame *pf);
int  pf_check(struct parse_frame *frm, chunk_t *pc);


/*
 * width.cpp
 */
void do_code_width(void);


/*
 * lang_pawn.cpp
 */
void pawn_prescan(void);
void pawn_add_virtual_semicolons();
chunk_t *pawn_check_vsemicolon(chunk_t *pc);


/*
 * universalindentgui.cpp
 */
void print_universal_indent_cfg(FILE *pfile);


/**
 * Advances to the next tab stop.
 * Column 1 is the left-most column.
 *
 * @param col     The current column
 * @param tabsize The tabsize
 * @return the next tabstop column
 */
static_inline
int calc_next_tab_column(int col, int tabsize)
{
   if (col <= 0)
   {
      col = 1;
   }
   col = 1 + ((((col - 1) / tabsize) + 1) * tabsize);
   return(col);
}

/**
 * Advances to the next tab stop for output.
 *
 * @param col  The current column
 * @return the next tabstop column
 */
static_inline
int next_tab_column(int col)
{
   return(calc_next_tab_column(col, cpd.settings[UO_output_tab_size].n));
}

/**
 * Advances to the next tab stop if not currently on one.
 *
 * @param col  The current column
 * @return the next tabstop column
 */
static_inline
int align_tab_column(int col)
{
   if ((col % cpd.settings[UO_output_tab_size].n) != 1)
   {
      calc_next_tab_column(col, cpd.settings[UO_output_tab_size].n);
   }
   return(col);
}


#endif   /* C_PARSE_PROTOTYPES_H_INCLUDED */
