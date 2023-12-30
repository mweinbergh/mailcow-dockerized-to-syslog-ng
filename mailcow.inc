source "s_mailcow_`MC_APP`" { udp(port(`MC_PORT`) ); };
template "t_mailcow_`MC_APP`_TS_no" {
	template ("${MESSAGE}\n"); 
	template_escape(no);
};
template "t_mailcow_`MC_APP`_TS_yes" {
	template ("${YEAR}-${MONTH}-${DAY} ${HOUR}:${MIN}:${SEC} ${MESSAGE}\n"); 
	template_escape(no);
};
rewrite "r_mailcow_`MC_APP`" {
	# remove escape sequences, like color
	subst("\x1b\[[0-9;]*[a-zA-Z]", "", value("MESSAGE"), flags(global));
};
destination "d_mailcow_`MC_APP`" {
	file(
		"/var/log/mailcow/`MC_APP`.log"
		persist-name("d_mailcow_`MC_APP`")
        template("t_mailcow_`MC_APP`_TS_`MC_ADD_TS`")
		create-dirs(yes)
	);
};
log { 
	source("s_mailcow_`MC_APP`");
	rewrite("r_mailcow_`MC_APP`");
	destination("d_mailcow_`MC_APP`");
	flags(final);
};
@define MC_ADD_TS "no"
# vim:ft=syslog-ng:ai:ts=4:
