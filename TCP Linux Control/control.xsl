<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:template match='/'>
<HTML>
	<HEAD>
	<TITLE>Informacion relacionada al socket <xsl:value-of select="./control/nombre"/></TITLE>
	</HEAD>
	<BODY>
	<P Align="center"><H2>Evolucion de la conexion entre los sockets local <xsl:value-of select="./control/local"/> y remoto <xsl:value-of select="./control/remoto"/></H2></P>
	<xsl:for-each select="/control/elemento">
	<P><FONT size="2">Datos del socket <xsl:value-of select="/control/nombre"/> a los <xsl:value-of select="./instante"/> segundos de conexion</FONT></P>
	<P></P>
	<P align="center"><TABLE>
	<TR><TD>PARAMETRO</TD><TD>VALOR</TD></TR>
	<TR><TD><A HREF="#state">state</A></TD><TD><xsl:value-of select="./state"/></TD></TR>
	<TR><TD><A HREF="#ca_state">ca_state</A></TD><TD><xsl:value-of select="./ca_state"/></TD></TR>
	<TR><TD><A HREF="#retransmits">retransmits</A></TD><TD><xsl:value-of select="./retransmits"/></TD></TR>
	<TR><TD><A HREF="#probes">probes</A></TD><TD><xsl:value-of select="./probes"/></TD></TR>
	<TR><TD><A HREF="#backoff">backoff</A></TD><TD><xsl:value-of select="./backoff"/></TD></TR>
	<TR><TD><A HREF="#snd_wscale">snd_wscale</A></TD><TD><xsl:value-of select="./snd_wscale"/></TD></TR>
	<TR><TD><A HREF="#rcv_wscale">rcv_wscale</A></TD><TD><xsl:value-of select="./rcv_wscale"/></TD></TR>
	<TR><TD><A HREF="#rto">rto</A></TD><TD><xsl:value-of select="./rto"/> us</TD></TR>
	<TR><TD><A HREF="#ato">ato</A></TD><TD><xsl:value-of select="./ato"/> us</TD></TR>
	<TR><TD><A HREF="#snd_mss">snd_mss</A></TD><TD><xsl:value-of select="./snd_mss"/> bytes</TD></TR>
	<TR><TD><A HREF="#rcv_mss">rcv_mss</A></TD><TD><xsl:value-of select="./rcv_mss"/> bytes</TD></TR>
	<TR><TD><A HREF="#unacked">unacked</A></TD><TD><xsl:value-of select="./unacked"/></TD></TR>
	<TR><TD><A HREF="#sacked">sacked</A></TD><TD><xsl:value-of select="./sacked"/></TD></TR>
	<TR><TD><A HREF="#lost">lost</A></TD><TD><xsl:value-of select="./lost"/></TD></TR>
	<TR><TD><A HREF="#retrans">retrans</A></TD><TD><xsl:value-of select="./retrans"/></TD></TR>
	<TR><TD><A HREF="#fackets">fackets</A></TD><TD><xsl:value-of select="./fackets"/></TD></TR>
	<TR><TD><A HREF="#last_data_sent">last_data_sent</A></TD><TD><xsl:value-of select="./last_data_sent"/> ms</TD></TR>
	<TR><TD><A HREF="#last_ack_sent">last_ack_sent</A></TD><TD><xsl:value-of select="./last_ack_sent"/> ms</TD></TR>
	<TR><TD><A HREF="#last_data_recv">last_data_recv</A></TD><TD><xsl:value-of select="./last_data_recv"/> ms</TD></TR>
	<TR><TD><A HREF="#last_ack_recv">last_ack_recv</A></TD><TD><xsl:value-of select="./last_ack_recv"/> ms</TD></TR>
	<TR><TD><A HREF="#pmtu">pmtu</A></TD><TD><xsl:value-of select="./pmtu"/> bytes</TD></TR>
	<TR><TD><A HREF="#rcv_ssthresh">rcv_ssthresh</A></TD><TD><xsl:value-of select="./rcv_ssthresh"/> bytes</TD></TR>
	<TR><TD><A HREF="#rtt">rtt</A></TD><TD><xsl:value-of select="./rtt"/> ms</TD></TR>
	<TR><TD><A HREF="#rttvar">rttvar</A></TD><TD><xsl:value-of select="./rttvar"/> ms</TD></TR>
	<TR><TD><A HREF="#snd_ssthresh">snd_ssthresh</A></TD><TD><xsl:value-of select="./snd_ssthresh"/> segmentos</TD></TR>
	<TR><TD><A HREF="#snd_cwnd">snd_cwnd</A></TD><TD><xsl:value-of select="./snd_cwnd"/> segmentos</TD></TR>
	<TR><TD><A HREF="#advmss">advmss</A></TD><TD><xsl:value-of select="./advmss"/> bytes</TD></TR>
	<TR><TD><A HREF="#reordering">reordering</A></TD><TD><xsl:value-of select="./reordering"/></TD></TR>
	</TABLE></P>
	</xsl:for-each>
	<HR></HR>
	<BIG><U>DESCRIPCION DE LOS PARAMETROS PRESENTADOS</U></BIG><BR></BR>
	<A NAME="state"><B>PARAMETRO STATE</B></A>
	<DL>
		<DT><U>Descripcion</U></DT>
		<DD>Permite conocer el estado de TCP.</DD>
		<DT><U>Unidades</U></DT>
		<DD>Adimensional</DD>
	</DL>
	<A NAME="ca_state"><B>PARAMETRO CA_STATE</B></A>
	<DL>
		<DT><U>Descripcion</U></DT>
		<DD>Permite conocer el estado del algoritmo Fast Retransmit/Recovery.</DD>
		<DT><U>Unidades</U></DT>
		<DD>Adimensional</DD>
	</DL>
	<A NAME="retransmits"><B>PARAMETRO RETRANSMITS</B></A>
	<DL>
		<DT><U>Descripcion</U></DT>
		<DD>Permite conocer el numero de retransmisones realizadas hasta el momento, independientemente de que sea por perdida o por fin de timeout.</DD>
		<DT><U>Unidades</U></DT>
		<DD>Adimensional</DD>
	</DL>
	<A NAME="probes"><B>PARAMETRO PROBES</B></A>
	<DL>
		<DT><U>Descripcion</U></DT>
		<DD>Permite conocer el numero de pruebas de ventana 0 realizadas y no respondidas. Cuando llegue a un determinado valor, TCP dara por finalizada la conexion.</DD>
		<DT><U>Unidades</U></DT>
		<DD>Adimensional</DD>
	</DL>
	<A NAME="backoff"><B>PARAMETRO BACKOFF</B></A>
	<DL>
		<DT><U>Descripcion</U></DT>
		<DD>Exponente que se utiliza para calcular el tempoizador de retransmision <A HREF="#rto">rto</A>, en potencias de dos.</DD>
		<DT><U>Unidades</U></DT>
		<DD>Adimensional</DD>
	</DL>
	<A NAME="snd_wscale"><B>PARAMETRO SND_WSCALE</B></A>
	<DL>
		<DT><U>Descripcion</U></DT>
		<DD>Exponente recibido por el otro extremo que indica el incremento de ventana que estaria dispuesto a soportar. Este incremento es exponencial, en potencias de dos.</DD>
		<DT><U>Unidades</U></DT>
		<DD>Adimensional</DD>
	</DL>
	<A NAME="rcv_wscale"><B>PARAMETRO RCV_WSCALE</B></A>
	<DL>
		<DT><U>Descripcion</U></DT>
		<DD>Exponente enviado al otro extremo que indica el incremento de ventana que se estaria dispuesto a soportar. Este incremento es exponencial, en potencias de dos.</DD>
		<DT><U>Unidades</U></DT>
		<DD>Adimensional</DD>
	</DL>
	<A NAME="rto"><B>PARAMETRO RTO</B></A>
	<DL>
		<DT><U>Descripcion</U></DT>
		<DD>Temporizador de retransmision.</DD>
		<DT><U>Unidades</U></DT>
		<DD>Microsegundos</DD>
	</DL>
	<A NAME="ato"><B>PARAMETRO ATO</B></A>
	<DL>
		<DT><U>Descripcion</U></DT>
		<DD>Temporizador utilizado a la hora de decidir si un ACK se retrasa o si no va a llegar. Si el ACK llega en ese intervalo, se supone que se retrasa; si no, se supone que no va a llegar.</DD>
		<DT><U>Unidades</U></DT>
		<DD>Microsegundos</DD>
	</DL>
	<A NAME="snd_mss"><B>PARAMETRO SND_MSS</B></A>
	<DL>
		<DT><U>Descripcion</U></DT>
		<DD>Tama&#241;o maximo de segmento en cache.</DD>
		<DT><U>Unidades</U></DT>
		<DD>Bytes</DD>
	</DL>
	<A NAME="rcv_mss"><B>PARAMETRO RCV_MSS</B></A>
	<DL>
		<DT><U>Descripcion</U></DT>
		<DD>Estimacion del tama&#241;o maximo de segmento utilizado por el otro extremo.</DD>
		<DT><U>Unidades</U></DT>
		<DD>Bytes</DD>
	</DL>
	<A NAME="unacked"><B>PARAMETRO UNACKED</B></A>
	<DL>
		<DT><U>Descripcion</U></DT>
		<DD>Determina el numero de segmentos enviados pero que no han sido asentidos aun.</DD>
		<DT><U>Unidades</U></DT>
		<DD>Adimensional</DD>
	</DL>
	<A NAME="sacked"><B>PARAMETRO SACKED</B></A>
	<DL>
		<DT><U>Descripcion</U></DT>
		<DD>Total de huecos entre paquetes.</DD>
		<DT><U>Unidades</U></DT>
		<DD>Adimensional</DD>
	</DL>
	<A NAME="lost"><B>PARAMETRO LOST</B></A>
	<DL>
		<DT><U>Descripcion</U></DT>
		<DD>Paquetes perdidos en el transcurso de la comunicacion.</DD>
		<DT><U>Unidades</U></DT>
		<DD>Adimensional</DD>
	</DL>
	<A NAME="retrans"><B>PARAMETRO RETRANS</B></A>
	<DL>
		<DT><U>Descripcion</U></DT>
		<DD>Paquetes retransmitidos durante la comuncicacion.</DD>
		<DT><U>Unidades</U></DT>
		<DD>Adimensional</DD>
	</DL>
	<A NAME="fackets"><B>PARAMETRO FACKETS</B></A>
	<DL>
		<DT><U>Descripcion</U></DT>
		<DD>Si damos un paquete por perdido, se supone que tambien se han perdido el resto de paquetes anteriores de los que no teniamos ACK. Por tanto, este parametro indica el numero de paquetes que han permitido reconocer perdidas multiples durante el transcurso de la conexion.</DD>
		<DT><U>Unidades</U></DT>
		<DD>Adimensional</DD>
	</DL>
	<A NAME="last_data_sent"><B>PARAMETRO LAST_DATA_SENT</B></A>
	<DL>
		<DT><U>Descripcion</U></DT>
		<DD>Timestamp del ultimo paquete de datos enviado.</DD>
		<DT><U>Unidades</U></DT>
		<DD>Milisegundos</DD>
	</DL>
	<A NAME="last_ack_sent"><B>PARAMETRO LAST_ACK_SENT</B></A>
	<DL>
		<DT><U>Descripcion</U></DT>
		<DD>Timestamp del ultimo ACK enviado.</DD>
		<DT><U>Unidades</U></DT>
		<DD>Milisegundos</DD>
	</DL>
	<A NAME="last_data_recv"><B>PARAMETRO LAST_DATA_RECV</B></A>
	<DL>
		<DT><U>Descripcion</U></DT>
		<DD>Timestamp del ultimo paquete de datos recibido.</DD>
		<DT><U>Unidades</U></DT>
		<DD>Milisegundos</DD>
	</DL>
	<A NAME="last_ack_recv"><B>PARAMETRO LAST_ACK_RECV</B></A>
	<DL>
		<DT><U>Descripcion</U></DT>
		<DD>Timestamp del ultimo ACK recibido.</DD>
		<DT><U>Unidades</U></DT>
		<DD>Milisegundos</DD>
	</DL>
	<A NAME="pmtu"><B>PARAMETRO PMTU</B></A>
	<DL>
		<DT><U>Descripcion</U></DT>
		<DD>Ultima unidad máxima de transferencia del protocolo TCP vista por el socket.</DD>
		<DT><U>Unidades</U></DT>
		<DD>Bytes</DD>
	</DL>
	<A NAME="rcv_ssthresh"><B>PARAMETRO RCV_SSTHRESH</B></A>
	<DL>
		<DT><U>Descripcion</U></DT>
		<DD>Umbral de ventana de congestion que se permite conocer al otro extremo.</DD>
		<DT><U>Unidades</U></DT>
		<DD>bytes</DD>
	</DL>
	<A NAME="rtt"><B>PARAMETRO RTT</B></A>
	<DL>
		<DT><U>Descripcion</U></DT>
		<DD>Tiempo de 'echo' medido.</DD>
		<DT><U>Unidades</U></DT>
		<DD>Milisegundos</DD>
	</DL>
	<A NAME="rttvar"><B>PARAMETRO RTTVAR</B></A>
	<DL>
		<DT><U>Descripcion</U></DT>
		<DD>Desviacion estandar del parametro <A HREF="#rto">rto</A>.</DD>
		<DT><U>Unidades</U></DT>
		<DD>Milisegundos</DD>
	</DL>
	<A NAME="snd_ssthresh"><B>PARAMETRO SND_SSTHRESH</B></A>
	<DL>
		<DT><U>Descripcion</U></DT>
		<DD>Umbral de la ventana de congestion utilizado en los algoritmos slow start y fast retransmit/recovery. Por encima de este umbral estamos en fast retransmit/recovery y por debajo en slow start.</DD>
		<DT><U>Unidades</U></DT>
		<DD>Segmentos</DD>
	</DL>
	<A NAME="snd_cwnd"><B>PARAMETRO SND_CWND</B></A>
	<DL>
		<DT><U>Descripcion</U></DT>
		<DD>Tama&#241;o de la ventana de congestion. Esta ventana se utiliza conjuntamente con la ventana del algoritmo de ventana deslizante para determinar la cantidad de segmentos que se pueden poner en la red sin necesidad de recibir asentimiento.</DD>
		<DT><U>Unidades</U></DT>
		<DD>Segmentos</DD>
	</DL>
	<A NAME="advmss"><B>PARAMETRO ADVMSS</B></A>
	<DL>
		<DT><U>Descripcion</U></DT>
		<DD>Tama&#241;o maximo de segmento que se espera recibir del otro extremo.</DD>
		<DT><U>Unidades</U></DT>
		<DD>Bytes</DD>
	</DL>
	<A NAME="reordering"><B>PARAMETRO REORDERING</B></A>
	<DL>
		<DT><U>Descripcion</U></DT>
		<DD>Maximo desvio de orden con el que puede llegar un segmento sin considerarse error.</DD>
		<DT><U>Unidades</U></DT>
		<DD>Adimensional</DD>
	</DL>


	</BODY>
</HTML>
</xsl:template>
</xsl:stylesheet>
