PROG=proj

SRCS = proj.c game.c screens.c vbe.c keyboard.c timer.c utils.c mouse.c db.c rtc.c

# __LCOM_OPTIMIZED__ disables most of the LCF's overhead (and functionality!)
CPPFLAGS += -pedantic -D __LCOM_OPTIMIZED__

DPADD += ${LIBLCF}
LDADD += -llcf

.include <minix.lcom.mk>
