Q=@
BOOST=boost_1_57_0
BOOST_FLAGS=threading=multi threadapi=pthread toolset=gcc-arm --prefix=../local --disable-long-double \
			--without-context \
			--without-coroutine \
			--without-date_time \
			--without-log \
			--without-test \
			--without-atomic \
			--without-chrono \
			--without-graph \
			--without-graph_parallel \
			--without-math \
			--without-python \
			--without-regex \
			--without-serialization \
			--without-signals \
			--without-wave \
			--without-timer \
			--without-mpi \
			--without-program_options \
			--without-container \
			--without-iostreams \
			cxxflags=-Os 

all:
	$(Q)echo "=================== Build Boost C++ Library ==================="
	$(Q)if [ ! -d $(BOOST) ] ; then \
		tar zxf boost_1_57_0.tar.gz; \
		cd $(BOOST); \
		sh bootstrap.sh; \
		cp project-config.jam project-config.$$; \
		sed 's/using gcc ;/using gcc : arm : arm-linux-g++ ;/' project-config.$$ > project-config.jam; \
		rm -rf project-config.$$; \
		rmdir bin.v2\libs /s /q; \
		rmdir stage\lib /s /q; \
		./bjam install $(BOOST_FLAGS); \
	fi

install:
	$(Q)echo "do nothing so far"

clean: clean_all
									
clean_all:
	$(Q)rm -rf $(BOOST) local 
