# How-To: Save mailcow-dockerized logs permanently in local files
## Purpose

This is a guide on how to permanently store the logs of the individual Mailcow-dockerized containers in local files. In Mailcow-dockerized, a remote log server target is configured for each container to which the log messages are sent. The log server used is syslog-ng, which can, but does not have to, run on the same machine.

This How-To assumes that mailcow-dockerized is installed in the **/opt/** directory and that the syslog-ng configuration files are located in the **/etc/syslog-ng/conf.d/** directory. If you have installed them elsewhere, you must adjust the paths.

## Requirements

Mandatory: The **syslog-ng** package must be installed and the service **syslog-ng.service** started and enabled.

Optional packages for troubleshooting: **tcpdump** and **net-tools**

## Create the log directory

`mkdir /var/log/mailcow`

## Configure remote log server targets

Create this file:

#### /opt/mailcow-dockerized/docker-compose.override.yml

```yaml
version: '2.1'
services:

  dovecot-mailcow:
    logging:
      driver: "syslog"
      options:
        syslog-address: "udp://127.0.0.1:1514"
        syslog-facility: "local3"

  postfix-mailcow:
    logging:
      driver: "syslog"
      options:
        syslog-address: "udp://127.0.0.1:1515"
        syslog-facility: "local3"

  rspamd-mailcow:
    logging:
      driver: "syslog"
      options:
        syslog-address: "udp://127.0.0.1:1516"
        syslog-facility: "local3"

  clamd-mailcow:
    logging:
      driver: "syslog"
      options:
        syslog-address: "udp://127.0.0.1:1517"
        syslog-facility: "local3"

  netfilter-mailcow:
    logging:
      driver: "syslog"
      options:
        syslog-address: "udp://127.0.0.1:1518"
        syslog-facility: "local3"

  nginx-mailcow:
    logging:
      driver: "syslog"
      options:
        syslog-address: "udp://127.0.0.1:1519"
        syslog-facility: "local3"

  sogo-mailcow:
    logging:
      driver: "syslog"
      options:
        syslog-address: "udp://127.0.0.1:1520"
        syslog-facility: "local3"

  mysql-mailcow:
    logging:
      driver: "syslog"
      options:
        syslog-address: "udp://127.0.0.1:1521"
        syslog-facility: "local3"

  php-fpm-mailcow:
    logging:
      driver: "syslog"
      options:
        syslog-address: "udp://127.0.0.1:1522"
        syslog-facility: "local3"

  ofelia-mailcow:
    logging:
      driver: "syslog"
      options:
        syslog-address: "udp://127.0.0.1:1523"
        syslog-facility: "local3"

  olefy-mailcow:
    logging:
      driver: "syslog"
      options:
        syslog-address: "udp://127.0.0.1:1524"
        syslog-facility: "local3"

  dockerapi-mailcow:
    logging:
      driver: "syslog"
      options:
        syslog-address: "udp://127.0.0.1:1525"
        syslog-facility: "local3"

  acme-mailcow:
    logging:
      driver: "syslog"
      options:
        syslog-address: "udp://127.0.0.1:1526"
        syslog-facility: "local3"

  watchdog-mailcow:
    logging:
      driver: "syslog"
      options:
        syslog-address: "udp://127.0.0.1:1527"
        syslog-facility: "local3"

  redis-mailcow:
    logging:
      driver: "syslog"
      options:
        syslog-address: "udp://127.0.0.1:1528"
        syslog-facility: "local3"
```

## Restart the Mailcow containers

`cd /opt/mailcow-dockerized; docker compose down; docker compose up -d; cd -`

## Syslog-NG config files

Create the following two files:

Comment out the `@include` lines of the logs you are not interested in.

#### /etc/syslog-ng/conf.d/99-mailcow.conf

```bash
# Mailcow Dovecot
@define MC_PORT 1514
@define MC_APP "dovecot"
@include "/etc/syslog-ng/conf.d/mailcow.inc"

# Mailcow Postfix
@define MC_PORT 1515
@define MC_APP "postfix"
@include "/etc/syslog-ng/conf.d/mailcow.inc"

# Mailcow Rspamd
@define MC_PORT 1516
@define MC_APP "rspamd"
@include "/etc/syslog-ng/conf.d/mailcow.inc"

# Mailcow Clamd
@define MC_PORT 1517
@define MC_APP "clamd"
@include "/etc/syslog-ng/conf.d/mailcow.inc"

# Mailcow netfilter
@define MC_PORT 1518
@define MC_APP "netfilter"
@define MC_ADD_TS "yes"
@include "/etc/syslog-ng/conf.d/mailcow.inc"

# Mailcow nginx
@define MC_PORT 1519
@define MC_APP "nginx"
@include "/etc/syslog-ng/conf.d/mailcow.inc"

# Mailcow SOGo
@define MC_PORT 1520
@define MC_APP "sogo"
@include "/etc/syslog-ng/conf.d/mailcow.inc"

# Mailcow MariaDB
@define MC_PORT 1521
@define MC_APP "mysql"
@include "/etc/syslog-ng/conf.d/mailcow.inc"

# Mailcow PHP fpm
@define MC_PORT 1522
@define MC_APP "php-fpm"
@include "/etc/syslog-ng/conf.d/mailcow.inc"

# Mailcow Ofelia
@define MC_PORT 1523
@define MC_APP "ofelia"
@include "/etc/syslog-ng/conf.d/mailcow.inc"

# Mailcow Olefy
@define MC_PORT 1524
@define MC_APP "olefy"
@define MC_ADD_TS "yes"
@include "/etc/syslog-ng/conf.d/mailcow.inc"

# Mailcow Docker API
@define MC_PORT 1525
@define MC_APP "dockerapi"
@define MC_ADD_TS "yes"
@include "/etc/syslog-ng/conf.d/mailcow.inc"

# Mailcow ACME
@define MC_PORT 1526
@define MC_APP "acme"
@include "/etc/syslog-ng/conf.d/mailcow.inc"

# Mailcow Watchdog
@define MC_PORT 1527
@define MC_APP "watchdog"
@include "/etc/syslog-ng/conf.d/mailcow.inc"

# Mailcow Redis
@define MC_PORT 1528
@define MC_APP "redis"
@include "/etc/syslog-ng/conf.d/mailcow.inc"

# vim:ft=syslog-ng:ai:ts=4:
```

#### /etc/syslog-ng/conf.d/mailcow.inc

```bash
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
```

## Restart Syslog-NG service

`systemctl restart syslog-ng`

## Log Rotation

Change the parameters according to your needs

#### /etc/logrotate.d/mailcow

```bash
/var/log/mailcow/*log {
    create 0600 root root
    weekly
    rotate 26
    missingok
    notifempty
    compress
    sharedscripts
    postrotate
       syslog-ng-ctl reload 
    endscript
}
```

## Connection check and troubleshooting

Packages **tcpdump** and **net-tools** must be installed.

Command to check whether the connections to the log ports have been established

`netstat -an | egrep ":15[12][0-9] " | sort`

Command to check whether syslog-ng is receiving data at the ports

`tcpdump -vv -A -ni any portrange 1514-1528`
