Name:		jabanner
Version:	0.1.1
Release:	1%{?dist}
Summary:	Just Another Banner

Group:		Applications/Text
License:	GPLv3
URL:		https://github.com/takei-yuya/jabanner
Source:	        https://github.com/takei-yuya/jabanner/releases/download/v0.1.1/jabanner-0.1.1.tar.gz
BuildRoot:	%(mktemp -ud %{_tmppath}/%{name}-%{version}-%{release}-XXXXXX)

BuildRequires:	vlgothic-p-fonts gd-devel
Requires:	vlgothic-p-fonts gd

%description
Just Another Banner

       XX            XX
       XXX           XXX
       XXX           XXX
       XXX           XXX
       XXX           XXX
       XXX   XXXXX   XXXXXXX      XXXXX   XX XXXX   XX XXXX     XXXXX    XX XX
       XXX  XXXXXXX  XXXXXXXX    XXXXXXX  XXXXXXXX  XXXXXXXX   XXXXXXX   XXXXX
       XXX XXX  XXX  XXXX XXXX  XXX  XXX  XXXX XXX  XXXX XXX  XXX  XXX   XXXXX
       XXX XXX  XXX  XXX   XXX  XXX  XXX  XXX   XX  XXX   XX  XXX   XXX  XXX
       XXX     XXXX  XXX   XXX      XXXX  XXX   XX  XXX   XX  XXXXXXXXX  XXX
       XXX  XXXXXXX  XXX   XXX   XXXXXXX  XXX   XX  XXX   XX  XXXXXXXXX  XXX
 XXX   XXX XXXXXXXX  XXX   XXX  XXXXXXXX  XXX   XX  XXX   XX  XXXXXXXXX  XXX
 XXX   XX  XXX   XX  XXX   XXX  XXX   XX  XXX   XX  XXX   XX  XXX        XXX
 XXX   XX  XX   XXX  XXX   XXX  XX   XXX  XXX   XX  XXX   XX  XXX   XXX  XXX
 XXXXXXXX  XXX  XXX  XXXX XXX   XXX  XXX  XXX   XX  XXX   XX  XXXX XXX   XXX
  XXXXXXX  XXXXXXXX  XXXXXXXX   XXXXXXXX  XXX   XX  XXX   XX   XXXXXXX   XXX
   XXXXX    XXXX XXX XX XXXX     XXXX XXX XX    XX  XX    XX    XXXXX    XX

Make banner like banner(1), but use font data.

%prep
%setup -q


%build
./configure --prefix=/usr --enable-font=/usr/share/fonts/vlgothic/VL-PGothic-Regular.ttf
make %{?_smp_mflags}


%install
rm -rf %{buildroot}
make install DESTDIR=%{buildroot}


%clean
rm -rf %{buildroot}


%files
/usr/bin/jabanner

%defattr(-,root,root,-)
%doc
%changelog

