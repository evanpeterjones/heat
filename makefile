OBJ = ctrl.o ctrlr.o post.o heater.o



ctrlr.o: headers/command.h headers/ctrlr.h

ctrl.o: curl/curl.h curl/easy.h

heater.o: headers/heater.h curl/curl.h
