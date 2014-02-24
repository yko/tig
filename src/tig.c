/* Copyright (c) 2006-2014 Jonas Fonseca <jonas.fonseca@gmail.com>
#include "request.h"
#include "line.h"
#include "keys.h"
#include "view.h"
#include "repo.h"
#define OPTION_INFO(_) \
	_(author_width,			int) \
	_(blame_options,		const char **) \
	_(commit_order,			enum commit_order) \
	_(diff_context,			int) \
	_(diff_options,			const char **) \
	_(editor_line_number,		bool) \
	_(focus_child,			bool) \
	_(horizontal_scroll,		double) \
	_(id_width,			int) \
	_(ignore_case,			bool) \
	_(ignore_space,			enum ignore_space) \
	_(line_graphics,		enum graphic) \
	_(line_number_interval,		int) \
	_(mouse,			bool) \
	_(mouse_scroll,			int) \
	_(read_git_colors,		bool) \
	_(scale_vsplit_view,		double) \
	_(show_author,			enum author) \
	_(show_changes,			bool) \
	_(show_date,			enum date) \
	_(show_file_size,		enum file_size) \
	_(show_filename,		enum filename) \
	_(show_filename_width,		int) \
	_(show_id,			bool) \
	_(show_line_numbers,		bool) \
	_(show_notes,			bool) \
	_(show_refs,			bool) \
	_(show_rev_graph,		bool) \
	_(split_view_height,		double) \
	_(status_untracked_dirs,	bool) \
	_(tab_size,			int) \
	_(title_overflow,		int) \
	_(vertical_split,		enum vertical_split) \
	_(wrap_lines,			bool) \

#define DEFINE_OPTION_EXTERNS(name, type) type opt_##name;
OPTION_INFO(DEFINE_OPTION_EXTERNS);
		return width * VSPLIT_SCALE > (height - 1) * 2;
	if (opt_show_notes) {
		info = find_line_info(argv[0], strlen(argv[0]), FALSE);
		info = get_line_info(index);
		return parse_args(&opt_blame_options, argv + 2);
		return parse_args(&opt_diff_options, argv + 2);
		return parse_enum(&opt_show_author, argv[2], author_map);
		return parse_enum(&opt_show_date, argv[2], date_map);
		return parse_bool(&opt_show_rev_graph, argv[2]);
		enum status_code res = parse_bool_matched(&opt_show_notes, argv[2], &matched);
		opt_show_notes = TRUE;
		return parse_bool(&opt_show_line_numbers, argv[2]);
		return parse_int(&opt_line_number_interval, argv[2], 1, 1024);
		return parse_int(&opt_show_filename_width, argv[2], 0, 1024);
		return parse_enum(&opt_show_filename, argv[2], filename_map);
		return parse_enum(&opt_show_file_size, argv[2], file_size_map);
		return parse_step(&opt_horizontal_scroll, argv[2]);
		return parse_step(&opt_split_view_height, argv[2]);
		return parse_bool(&opt_status_untracked_dirs, argv[2]);
		return parse_id(&opt_id_width, argv[2]);
		bool enabled = FALSE;
		code = parse_bool_matched(&enabled, argv[2], &matched);
			if (enabled)
			if (code != SUCCESS)
				opt_title_overflow = 50;
		return parse_bool(&opt_editor_line_number, argv[2]);
		return parse_int(&opt_mouse_scroll, argv[2], 0, 1024);
	const bool diff_opts_from_args = !!opt_diff_options;
		else if (!argv_copy(&opt_diff_options, diff_opts))
	draw_text_overflow(view, text, opt_title_overflow > 0, opt_title_overflow + offset, LINE_DEFAULT)
	const char *date = mkdate(time, opt_show_date);
	int cols = opt_show_date == DATE_SHORT ? DATE_SHORT_WIDTH : DATE_WIDTH;
	if (opt_show_date == DATE_NO)
	const char *text = mkauthor(author, opt_author_width, opt_show_author);
	if (opt_show_author == AUTHOR_NO)
	return draw_id_custom(view, LINE_ID, id, opt_id_width);
	bool trim = filename && strlen(filename) >= opt_show_filename_width;
	if (opt_show_filename == FILENAME_NO)
	if (opt_show_filename == FILENAME_AUTO && !auto_enabled)
	return draw_field(view, LINE_FILENAME, filename, opt_show_filename_width, ALIGN_LEFT, trim);
	const char *str = pad ? NULL : mkfilesize(size, opt_show_file_size);
	if (!width || opt_show_file_size == FILE_SIZE_NO)
	if (!opt_show_line_numbers)
	if (lineno == 1 || (lineno % opt_line_number_interval) == 0) {
	view->height  = apply_step(opt_split_view_height, base->height);
	view->width  = apply_step(VSPLIT_SCALE, base->width);
	_(LINENO,    '.', "line numbers",      &opt_show_line_numbers, NULL, VIEW_NO_FLAGS), \
	_(DATE,      'D', "dates",             &opt_show_date, date_map, VIEW_NO_FLAGS), \
	_(AUTHOR,    'A', "author",            &opt_show_author, author_map, VIEW_NO_FLAGS), \
	_(REV_GRAPH, 'g', "revision graph",    &opt_show_rev_graph, NULL, VIEW_LOG_LIKE), \
	_(FILENAME,  '#', "file names",        &opt_show_filename, filename_map, VIEW_NO_FLAGS), \
	_(FILE_SIZE, '*', "file sizes",        &opt_show_file_size, file_size_map, VIEW_NO_FLAGS), \
	_(TITLE_OVERFLOW, '$', "commit title overflow display", &opt_title_overflow, NULL, VIEW_NO_FLAGS), \
	_(UNTRACKED_DIRS, 'd', "untracked directory info", &opt_status_untracked_dirs, NULL, VIEW_STATUS_LIKE), \
	} else if (menu[i].data == &opt_title_overflow) {
		int *option = menu[i].data;

		*option = *option ? -*option : 50;
		string_format_size(msg, SIZEOF_STR,
			"%sabling %s", *option > 0 ? "En" : "Dis", menu[i].text);

		lines = opt_mouse_scroll;
		if (view->pos.col <= apply_step(opt_horizontal_scroll, view->width))
			view->pos.col -= apply_step(opt_horizontal_scroll, view->width);
		view->pos.col += apply_step(opt_horizontal_scroll, view->width);
			if (!format_append_argv(&format, dst_argv, opt_diff_options))
			if (!format_append_argv(&format, dst_argv, opt_blame_options))
			if (opt_show_line_numbers || view_has_flags(view, VIEW_ALWAYS_LINENO))
	if (!view_has_flags(view, VIEW_NO_GIT_DIR) && !repo.git_dir[0]) {
	open_external_viewer(mergetool_argv, repo.cdup, TRUE, "");
	if (lineno && opt_editor_line_number && string_format(lineno_cmd, "+%u", lineno))
	if (!open_external_viewer(editor_argv, repo.cdup, TRUE, EDITOR_LINENO_MSG))
		opt_editor_line_number = FALSE;
		const int len = get_line_info(LINE_DIFF_HEADER)->linelen;
	if (!io_run(&io, IO_RD, repo.cdup, opt_env, blame_argv))
	if (!prefixcmp(line, "@@ -"))
		line += STRING_SIZE("@@ -");
	else if (!prefixcmp(line, "@@@ -") &&
		 (line = strchr(line + STRING_SIZE("@@@ -"), '-')))
		line += 1;
	else
		if (chunk->type != LINE_DIFF_DEL &&
		    chunk->type != LINE_DIFF_DEL2)
	bool has_path = file && string_format(path, "%s%s", repo.cdup, file);
struct help_request_iterator {
	struct view *view;
	struct keymap *keymap;
	bool add_title;
	const char *group;
};
static bool
help_open_keymap(void *data, const struct request_info *req_info, const char *group)
{
	struct help_request_iterator *iterator = data;
	struct view *view = iterator->view;
	struct keymap *keymap = iterator->keymap;
	const char *key = get_keys(keymap, req_info->request, TRUE);
	if (req_info->request == REQ_NONE || !key || !*key)
		return TRUE;
	if (iterator->add_title && help_open_keymap_title(view, keymap))
		return FALSE;
	iterator->add_title = FALSE;
	if (iterator->group != group) {
		add_line_text(view, group, LINE_HELP_GROUP);
		iterator->group = group;
	add_line_format(view, LINE_DEFAULT, "    %-25s %-20s %s", key,
			enum_name(*req_info), req_info->help);
	return TRUE;
}

static void
help_open_keymap_run_requests(struct help_request_iterator *iterator)
{
	struct view *view = iterator->view;
	struct keymap *keymap = iterator->keymap;
	char buf[SIZEOF_STR];
	const char *group = "External commands:";
	int i;
	for (i = 0; TRUE; i++) {
		if (!req)
			break;

		if (req->keymap != keymap)
		if (iterator->add_title && help_open_keymap_title(view, keymap))
		iterator->add_title = FALSE;
	for (keymap = get_keymaps(); keymap; keymap = keymap->next) {
		struct help_request_iterator iterator = { view, keymap, TRUE };

		if (foreach_request(help_open_keymap, &iterator))
			help_open_keymap_run_requests(&iterator);
	}
		if (!begin_update(view, repo.cdup, log_file, OPEN_EXTRA)) {
		pos = strrchr(text, '\t');
		mkauthor(entry->author, opt_author_width, opt_show_author),
		mkdate(&entry->time, opt_show_date),
	if (view->lines == 0 && repo.prefix[0]) {
		char *pos = repo.prefix;
	return begin_update(view, repo.cdup, tree_argv, flags);
	if (opt_blame_options) {
		for (i = 0; opt_blame_options[i]; i++) {
			if (prefixcmp(opt_blame_options[i], "-C"))
	const char *file_argv[] = { repo.cdup, opt_file , NULL };
	if (!view->prev && *repo.prefix && !(flags & (OPEN_RELOAD | OPEN_REFRESH))) {
		if (!string_format(opt_file, "%s%s", repo.prefix, path)) {
	if (*opt_ref || !begin_update(view, repo.cdup, file_argv, flags)) {
		if (!begin_update(view, repo.cdup, blame_cat_file_argv, flags))
		if (view->lines == 0 || !begin_update(view, repo.cdup, blame_argv, OPEN_EXTRA)) {
	if (draw_id_custom(view, id_type, id, opt_id_width))
		commit ? mkauthor(commit->author, opt_author_width, opt_show_author) : "",
		commit ? mkdate(&commit->time, opt_show_date) : "",
		mkauthor(branch->author, opt_author_width, opt_show_author),
	if (!io_run(&io, IO_RD, repo.cdup, opt_env, argv))
	"git", "ls-files", "-z", "--others", "--exclude-standard", repo.prefix, NULL, NULL,
		char *head = repo.head;
		if (!string_format(buf, "%s/%s", repo.git_dir, paths[i][0]) ||
		if (!*repo.head) {
			if (io_open(&io, "%s/rebase-merge/head-name", repo.git_dir) &&
			string_copy(status_onbranch, repo.head);
	if (repo.is_inside_work_tree == FALSE) {
		opt_status_untracked_dirs ? NULL : "--directory";
		return io_run(io, IO_WR, repo.cdup, opt_env, staged_argv);
		return io_run(io, IO_WR, repo.cdup, opt_env, others_argv);
			if (!io_run_fg(reset_argv, repo.cdup))
		return io_run_fg(checkout_argv, repo.cdup);
	if (!io_run(&io, IO_WR, repo.cdup, opt_env, apply_argv))
	static const char *file_argv[] = { repo.cdup, stage_status.new.name, NULL };
	view->dir = repo.cdup;
	state->with_graph = opt_show_rev_graph &&
		if (!state->added_changes_commits && opt_show_changes && repo.is_inside_work_tree)
		mkauthor(commit->author, opt_author_width, opt_show_author),
		mkdate(&commit->time, opt_show_date),
		string_ncopy(repo.remote, value, valuelen);
	} else if (*repo.remote && !strcmp(name, ".merge")) {
		size_t from = strlen(repo.remote);
		if (!string_format_from(repo.remote, &from, "/%s", value))
			repo.remote[0] = 0;
	if (chdir(repo.git_dir) < 0)
		die("Failed to chdir(%s): %s", repo.git_dir, strerror(errno));
	if (!getcwd(repo.git_dir, sizeof(repo.git_dir)))
	if (setenv("GIT_DIR", repo.git_dir, TRUE))
		die("Failed to set GIT_DIR to '%s'", repo.git_dir);
	repo.is_inside_work_tree = TRUE;
	struct line_info *info = get_line_info(type);
		parse_id(&opt_id_width, value);
	else if (*repo.head && !prefixcmp(name, "branch.") &&
		 !strncmp(name + 7, repo.head, strlen(repo.head)))
		set_remote_branch(name + 7 + strlen(repo.head), value, valuelen);
			opt_blame_options = flags;
	if (!repo.git_dir[0] && request != REQ_VIEW_PAGER)