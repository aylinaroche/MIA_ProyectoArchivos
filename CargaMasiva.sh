
sqlplus Becas/pass @/home/aylin/Documentos/Scripts/TablasTemporales.sql
echo SE HAN CREADO LAS TABLAS TEMPORALES CORRECTAMENTE.
pause;

sqlldr userid=Becas/pass control=/home/aylin/Documentos/Ejecutables/archivoEstudiante.ctl
echo SE HAN AGREGADO LOS DATOS ESTUDIANTE CORRECTAMENTE.
pause;

sqlldr userid=Becas/pass control=/home/aylin/Documentos/Ejecutables/archivoSolicitud.ctl
echo SE HAN AGREGADO LOS DATOS SOLICITUD CORRECTAMENTE.
pause;

sqlplus Becas/pass @/home/aylin/Documentos/Scripts/LlenarTablas.sql
echo SE HAN LLENADO LAS TABLAS CORRECTAMENTE.
pause;
exit; 