Name:		jabanner
Version:	0.1.1
Release:	1%{?dist}
Summary:	Just Another Banner

Group:		Applications/Text
License:	GPLv3
URL:		https://github.com/takei-yuya/jabanner
Source:	        https://github.com/takei-yuya/jabanner/releases/download/v0.1.1/jabanner-0.1.1.tar.gz
BuildRoot:	%(mktemp -ud %{_tmppath}/%{name}-%{version}-%{release}-XXXXXX)

BuildRequires:	gd-devel
Requires:	gd

%description
Just Another Banner

%prep
%setup -q


%build
./configure --prefix=/usr
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

