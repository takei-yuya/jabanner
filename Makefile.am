SUBDIRS= src
#AUTOMAKE_OPTIONS = foreign

src/jabanner: config.h

ACLOCAL_AMFLAGS = -I m4

EXTRA_DIST = config.rpath autogen.sh jabanner.spec find_font.sh

$(PACKAGE)-$(VERSION)-1.el6.x86_64.rpm: $(PACKAGE)-$(VERSION).tar.gz docker-centos6/Dockerfile
	cp $(PACKAGE)-$(VERSION).tar.gz docker-centos6/
	docker build -t docker-$(PACKAGE)-$(VERSION)-centos6 docker-centos6
	docker run -v $(abs_top_builddir):/tmp/output/ docker-$(PACKAGE)-$(VERSION)-centos6

$(PACKAGE)-$(VERSION)-1.el7.x86_64.rpm: $(PACKAGE)-$(VERSION).tar.gz docker-centos7/Dockerfile
	cp $(PACKAGE)-$(VERSION).tar.gz docker-centos7/
	docker build -t docker-$(PACKAGE)-$(VERSION)-centos7 docker-centos7
	docker run -v $(abs_top_builddir):/tmp/output/ docker-$(PACKAGE)-$(VERSION)-centos7
