#!/bin/sh
# This script was generated using Makeself 2.3.0

ORIG_UMASK=`umask`
if test "n" = n; then
    umask 077
fi

CRCsum="136016668"
MD5="e44691011da04371f82584a59e004d09"
TMPROOT=${TMPDIR:=/tmp}
USER_PWD="$PWD"; export USER_PWD

label="Extracting potd-q27"
script="echo"
scriptargs="The initial files can be found in the newly created directory: potd-q27"
licensetxt=""
helpheader=''
targetdir="potd-q27"
filesizes="10381"
keep="y"
nooverwrite="n"
quiet="n"
nodiskspace="n"

print_cmd_arg=""
if type printf > /dev/null; then
    print_cmd="printf"
elif test -x /usr/ucb/echo; then
    print_cmd="/usr/ucb/echo"
else
    print_cmd="echo"
fi

unset CDPATH

MS_Printf()
{
    $print_cmd $print_cmd_arg "$1"
}

MS_PrintLicense()
{
  if test x"$licensetxt" != x; then
    echo "$licensetxt"
    while true
    do
      MS_Printf "Please type y to accept, n otherwise: "
      read yn
      if test x"$yn" = xn; then
        keep=n
	eval $finish; exit 1
        break;
      elif test x"$yn" = xy; then
        break;
      fi
    done
  fi
}

MS_diskspace()
{
	(
	if test -d /usr/xpg4/bin; then
		PATH=/usr/xpg4/bin:$PATH
	fi
	df -kP "$1" | tail -1 | awk '{ if ($4 ~ /%/) {print $3} else {print $4} }'
	)
}

MS_dd()
{
    blocks=`expr $3 / 1024`
    bytes=`expr $3 % 1024`
    dd if="$1" ibs=$2 skip=1 obs=1024 conv=sync 2> /dev/null | \
    { test $blocks -gt 0 && dd ibs=1024 obs=1024 count=$blocks ; \
      test $bytes  -gt 0 && dd ibs=1 obs=1024 count=$bytes ; } 2> /dev/null
}

MS_dd_Progress()
{
    if test x"$noprogress" = xy; then
        MS_dd $@
        return $?
    fi
    file="$1"
    offset=$2
    length=$3
    pos=0
    bsize=4194304
    while test $bsize -gt $length; do
        bsize=`expr $bsize / 4`
    done
    blocks=`expr $length / $bsize`
    bytes=`expr $length % $bsize`
    (
        dd ibs=$offset skip=1 2>/dev/null
        pos=`expr $pos \+ $bsize`
        MS_Printf "     0%% " 1>&2
        if test $blocks -gt 0; then
            while test $pos -le $length; do
                dd bs=$bsize count=1 2>/dev/null
                pcent=`expr $length / 100`
                pcent=`expr $pos / $pcent`
                if test $pcent -lt 100; then
                    MS_Printf "\b\b\b\b\b\b\b" 1>&2
                    if test $pcent -lt 10; then
                        MS_Printf "    $pcent%% " 1>&2
                    else
                        MS_Printf "   $pcent%% " 1>&2
                    fi
                fi
                pos=`expr $pos \+ $bsize`
            done
        fi
        if test $bytes -gt 0; then
            dd bs=$bytes count=1 2>/dev/null
        fi
        MS_Printf "\b\b\b\b\b\b\b" 1>&2
        MS_Printf " 100%%  " 1>&2
    ) < "$file"
}

MS_Help()
{
    cat << EOH >&2
${helpheader}Makeself version 2.3.0
 1) Getting help or info about $0 :
  $0 --help   Print this message
  $0 --info   Print embedded info : title, default target directory, embedded script ...
  $0 --lsm    Print embedded lsm entry (or no LSM)
  $0 --list   Print the list of files in the archive
  $0 --check  Checks integrity of the archive

 2) Running $0 :
  $0 [options] [--] [additional arguments to embedded script]
  with following options (in that order)
  --confirm             Ask before running embedded script
  --quiet		Do not print anything except error messages
  --noexec              Do not run embedded script
  --keep                Do not erase target directory after running
			the embedded script
  --noprogress          Do not show the progress during the decompression
  --nox11               Do not spawn an xterm
  --nochown             Do not give the extracted files to the current user
  --nodiskspace         Do not check for available disk space
  --target dir          Extract directly to a target directory
                        directory path can be either absolute or relative
  --tar arg1 [arg2 ...] Access the contents of the archive through the tar command
  --                    Following arguments will be passed to the embedded script
EOH
}

MS_Check()
{
    OLD_PATH="$PATH"
    PATH=${GUESS_MD5_PATH:-"$OLD_PATH:/bin:/usr/bin:/sbin:/usr/local/ssl/bin:/usr/local/bin:/opt/openssl/bin"}
	MD5_ARG=""
    MD5_PATH=`exec <&- 2>&-; which md5sum || command -v md5sum || type md5sum`
    test -x "$MD5_PATH" || MD5_PATH=`exec <&- 2>&-; which md5 || command -v md5 || type md5`
	test -x "$MD5_PATH" || MD5_PATH=`exec <&- 2>&-; which digest || command -v digest || type digest`
    PATH="$OLD_PATH"

    if test x"$quiet" = xn; then
		MS_Printf "Verifying archive integrity..."
    fi
    offset=`head -n 532 "$1" | wc -c | tr -d " "`
    verb=$2
    i=1
    for s in $filesizes
    do
		crc=`echo $CRCsum | cut -d" " -f$i`
		if test -x "$MD5_PATH"; then
			if test x"`basename $MD5_PATH`" = xdigest; then
				MD5_ARG="-a md5"
			fi
			md5=`echo $MD5 | cut -d" " -f$i`
			if test x"$md5" = x00000000000000000000000000000000; then
				test x"$verb" = xy && echo " $1 does not contain an embedded MD5 checksum." >&2
			else
				md5sum=`MS_dd_Progress "$1" $offset $s | eval "$MD5_PATH $MD5_ARG" | cut -b-32`;
				if test x"$md5sum" != x"$md5"; then
					echo "Error in MD5 checksums: $md5sum is different from $md5" >&2
					exit 2
				else
					test x"$verb" = xy && MS_Printf " MD5 checksums are OK." >&2
				fi
				crc="0000000000"; verb=n
			fi
		fi
		if test x"$crc" = x0000000000; then
			test x"$verb" = xy && echo " $1 does not contain a CRC checksum." >&2
		else
			sum1=`MS_dd_Progress "$1" $offset $s | CMD_ENV=xpg4 cksum | awk '{print $1}'`
			if test x"$sum1" = x"$crc"; then
				test x"$verb" = xy && MS_Printf " CRC checksums are OK." >&2
			else
				echo "Error in checksums: $sum1 is different from $crc" >&2
				exit 2;
			fi
		fi
		i=`expr $i + 1`
		offset=`expr $offset + $s`
    done
    if test x"$quiet" = xn; then
		echo " All good."
    fi
}

UnTAR()
{
    if test x"$quiet" = xn; then
		tar $1vf - 2>&1 || { echo Extraction failed. > /dev/tty; kill -15 $$; }
    else

		tar $1f - 2>&1 || { echo Extraction failed. > /dev/tty; kill -15 $$; }
    fi
}

finish=true
xterm_loop=
noprogress=n
nox11=n
copy=none
ownership=y
verbose=n

initargs="$@"

while true
do
    case "$1" in
    -h | --help)
	MS_Help
	exit 0
	;;
    -q | --quiet)
	quiet=y
	noprogress=y
	shift
	;;
    --info)
	echo Identification: "$label"
	echo Target directory: "$targetdir"
	echo Uncompressed size: 96 KB
	echo Compression: gzip
	echo Date of packaging: Mon Mar  6 03:19:49 CST 2017
	echo Built with Makeself version 2.3.0 on linux-gnu
	echo Build command was: "makeself/makeself.sh \\
    \"--notemp\" \\
    \"../../questions/potd2_027_binaryTree_height/potd-q27\" \\
    \"potd-q27.sh\" \\
    \"Extracting potd-q27\" \\
    \"echo\" \\
    \"The initial files can be found in the newly created directory: potd-q27\""
	if test x"$script" != x; then
	    echo Script run after extraction:
	    echo "    " $script $scriptargs
	fi
	if test x"" = xcopy; then
		echo "Archive will copy itself to a temporary location"
	fi
	if test x"n" = xy; then
		echo "Root permissions required for extraction"
	fi
	if test x"y" = xy; then
	    echo "directory $targetdir is permanent"
	else
	    echo "$targetdir will be removed after extraction"
	fi
	exit 0
	;;
    --dumpconf)
	echo LABEL=\"$label\"
	echo SCRIPT=\"$script\"
	echo SCRIPTARGS=\"$scriptargs\"
	echo archdirname=\"potd-q27\"
	echo KEEP=y
	echo NOOVERWRITE=n
	echo COMPRESS=gzip
	echo filesizes=\"$filesizes\"
	echo CRCsum=\"$CRCsum\"
	echo MD5sum=\"$MD5\"
	echo OLDUSIZE=96
	echo OLDSKIP=533
	exit 0
	;;
    --lsm)
cat << EOLSM
No LSM.
EOLSM
	exit 0
	;;
    --list)
	echo Target directory: $targetdir
	offset=`head -n 532 "$0" | wc -c | tr -d " "`
	for s in $filesizes
	do
	    MS_dd "$0" $offset $s | eval "gzip -cd" | UnTAR t
	    offset=`expr $offset + $s`
	done
	exit 0
	;;
	--tar)
	offset=`head -n 532 "$0" | wc -c | tr -d " "`
	arg1="$2"
    if ! shift 2; then MS_Help; exit 1; fi
	for s in $filesizes
	do
	    MS_dd "$0" $offset $s | eval "gzip -cd" | tar "$arg1" - "$@"
	    offset=`expr $offset + $s`
	done
	exit 0
	;;
    --check)
	MS_Check "$0" y
	exit 0
	;;
    --confirm)
	verbose=y
	shift
	;;
	--noexec)
	script=""
	shift
	;;
    --keep)
	keep=y
	shift
	;;
    --target)
	keep=y
	targetdir=${2:-.}
    if ! shift 2; then MS_Help; exit 1; fi
	;;
    --noprogress)
	noprogress=y
	shift
	;;
    --nox11)
	nox11=y
	shift
	;;
    --nochown)
	ownership=n
	shift
	;;
    --nodiskspace)
	nodiskspace=y
	shift
	;;
    --xwin)
	if test "n" = n; then
		finish="echo Press Return to close this window...; read junk"
	fi
	xterm_loop=1
	shift
	;;
    --phase2)
	copy=phase2
	shift
	;;
    --)
	shift
	break ;;
    -*)
	echo Unrecognized flag : "$1" >&2
	MS_Help
	exit 1
	;;
    *)
	break ;;
    esac
done

if test x"$quiet" = xy -a x"$verbose" = xy; then
	echo Cannot be verbose and quiet at the same time. >&2
	exit 1
fi

if test x"n" = xy -a `id -u` -ne 0; then
	echo "Administrative privileges required for this archive (use su or sudo)" >&2
	exit 1	
fi

if test x"$copy" \!= xphase2; then
    MS_PrintLicense
fi

case "$copy" in
copy)
    tmpdir=$TMPROOT/makeself.$RANDOM.`date +"%y%m%d%H%M%S"`.$$
    mkdir "$tmpdir" || {
	echo "Could not create temporary directory $tmpdir" >&2
	exit 1
    }
    SCRIPT_COPY="$tmpdir/makeself"
    echo "Copying to a temporary location..." >&2
    cp "$0" "$SCRIPT_COPY"
    chmod +x "$SCRIPT_COPY"
    cd "$TMPROOT"
    exec "$SCRIPT_COPY" --phase2 -- $initargs
    ;;
phase2)
    finish="$finish ; rm -rf `dirname $0`"
    ;;
esac

if test x"$nox11" = xn; then
    if tty -s; then                 # Do we have a terminal?
	:
    else
        if test x"$DISPLAY" != x -a x"$xterm_loop" = x; then  # No, but do we have X?
            if xset q > /dev/null 2>&1; then # Check for valid DISPLAY variable
                GUESS_XTERMS="xterm gnome-terminal rxvt dtterm eterm Eterm xfce4-terminal lxterminal kvt konsole aterm terminology"
                for a in $GUESS_XTERMS; do
                    if type $a >/dev/null 2>&1; then
                        XTERM=$a
                        break
                    fi
                done
                chmod a+x $0 || echo Please add execution rights on $0
                if test `echo "$0" | cut -c1` = "/"; then # Spawn a terminal!
                    exec $XTERM -title "$label" -e "$0" --xwin "$initargs"
                else
                    exec $XTERM -title "$label" -e "./$0" --xwin "$initargs"
                fi
            fi
        fi
    fi
fi

if test x"$targetdir" = x.; then
    tmpdir="."
else
    if test x"$keep" = xy; then
	if test x"$nooverwrite" = xy && test -d "$targetdir"; then
            echo "Target directory $targetdir already exists, aborting." >&2
            exit 1
	fi
	if test x"$quiet" = xn; then
	    echo "Creating directory $targetdir" >&2
	fi
	tmpdir="$targetdir"
	dashp="-p"
    else
	tmpdir="$TMPROOT/selfgz$$$RANDOM"
	dashp=""
    fi
    mkdir $dashp $tmpdir || {
	echo 'Cannot create target directory' $tmpdir >&2
	echo 'You should try option --target dir' >&2
	eval $finish
	exit 1
    }
fi

location="`pwd`"
if test x"$SETUP_NOCHECK" != x1; then
    MS_Check "$0"
fi
offset=`head -n 532 "$0" | wc -c | tr -d " "`

if test x"$verbose" = xy; then
	MS_Printf "About to extract 96 KB in $tmpdir ... Proceed ? [Y/n] "
	read yn
	if test x"$yn" = xn; then
		eval $finish; exit 1
	fi
fi

if test x"$quiet" = xn; then
	MS_Printf "Uncompressing $label"
fi
res=3
if test x"$keep" = xn; then
    trap 'echo Signal caught, cleaning up >&2; cd $TMPROOT; /bin/rm -rf $tmpdir; eval $finish; exit 15' 1 2 3 15
fi

if test x"$nodiskspace" = xn; then
    leftspace=`MS_diskspace $tmpdir`
    if test -n "$leftspace"; then
        if test "$leftspace" -lt 96; then
            echo
            echo "Not enough space left in "`dirname $tmpdir`" ($leftspace KB) to decompress $0 (96 KB)" >&2
            echo "Use --nodiskspace option to skip this check and proceed anyway" >&2
            if test x"$keep" = xn; then
                echo "Consider setting TMPDIR to a directory with more free space."
            fi
            eval $finish; exit 1
        fi
    fi
fi

for s in $filesizes
do
    if MS_dd_Progress "$0" $offset $s | eval "gzip -cd" | ( cd "$tmpdir"; umask $ORIG_UMASK ; UnTAR xp ) 1>/dev/null; then
		if test x"$ownership" = xy; then
			(PATH=/usr/xpg4/bin:$PATH; cd "$tmpdir"; chown -R `id -u` .;  chgrp -R `id -g` .)
		fi
    else
		echo >&2
		echo "Unable to decompress $0" >&2
		eval $finish; exit 1
    fi
    offset=`expr $offset + $s`
done
if test x"$quiet" = xn; then
	echo
fi

cd "$tmpdir"
res=0
if test x"$script" != x; then
    if test x"$verbose" = x"y"; then
		MS_Printf "OK to execute: $script $scriptargs $* ? [Y/n] "
		read yn
		if test x"$yn" = x -o x"$yn" = xy -o x"$yn" = xY; then
			eval "\"$script\" $scriptargs \"\$@\""; res=$?;
		fi
    else
		eval "\"$script\" $scriptargs \"\$@\""; res=$?
    fi
    if test "$res" -ne 0; then
		test x"$verbose" = xy && echo "The program '$script' returned an error code ($res)" >&2
    fi
fi
if test x"$keep" = xn; then
    cd $TMPROOT
    /bin/rm -rf $tmpdir
fi
eval $finish; exit $res
‹ µ)½Xì]t\Åy»«•Ö»²õôêaË¾~"Ùhµ/=,#?Ö–lY6’MÁÜ¬V+iÍjWŞ‡&Æ¸P@€ƒ\ÒœÊIÚ@ÒœC¡Æi1‰5„œz›†“HCi€r ¤¡¸3sÿûİ±ØÒ½ÇÒÌÿÍ?ÿÿÏÜ™fî½¿ì®C—üòà«±¾yı^7€<Ş†F¯ßOq¸p™§¾Ñç4x	ŞèohDb=ºW&•%E„ú.ÈI¡?ÂË]·9tS¤/‹\Úûßpï½7 Şÿú@#.÷züõHôdïÿ%¿‚;‚«7Å«ÄÁP4îØ²fc7äİ	1ŒD:½wÂáX»c.ÇBñşåË	µ¾cõÂ[›J÷^^¾Ü3*Ö†ÅÚ~±v‹G¬ı“P,†GFÓÉ£c®jÇºÉ5ÌŞ,.®sj-OpbWcÆâêu5ââE’¡bjÄÚ„¸¸ÕáMn–Mfl%æniNfw8´F5kÄ4b€[7‹„âÍµÉA±¶O\†ûHgó—sş+ö9Îº6(şßGç¿ÏŸÿ—ãZ‡c™ŞˆØM¤ğ®r¨ØBmJ,tdRÑx¿FRC¡pDÄ“w¥Ã§é”«®ovˆâ6¨ Æ½WŠqşñãŸ f1äEúÒxâ/ûVÊ@2Ú? #~Šø4¹R8‘I·´,l‹PÆD®Ô,.liÁuû#i®®ii‰Ä{c+Mù}2¿oºü~™ß?]ş€Ì0ãÇ’‘t&=+û_Èù¯÷ŸÏü÷5øÙõ¿'Ùù9ç¿a®k. %Œçyo¤OçtÂÜ'(N ¹YÉaïĞ,’™]İ¹½££æJ‘Î{™o÷É~D«§›JÔ­À$ªõ~AgÑ—yÿ¯İ÷Ïkı÷û<ìü÷{²óÿòÌÿ¾8Ş¢´­+ìÜ².(µ9a °ÏæğŞ?•Ò67;†2=±h¸Y¿cXFüÃJB½„ª®!ñ:}V±¯¸Ñ¾¬søôó?ñùÌ<ñÌó<ÿ½ÙùY®ıÁõA°*´€VáŸÉWy…–o…ßsQÚŞ6şë¶ñ}¶İƒNæ‘‚¶“ì$İõBÁ|Z~ä<¾Ó®Â,9´¾ªÉáZf¡æ\GM[OX7ªl´Ì:Û’K2NÌb­²X)QEˆy+5ÅZaì‹‰™¬TH„f_¹õÔaØs79Iú .ÊİŒ¬ù´l‹Õş fÍRÌÊ½F†uH *²Ô±Ú&h!Ev
2Lİ S3Ó 	 ã‚
…ú¾QøĞ3˜ÖĞŠÒº¢ïk²oX“o&ÂŠTøî*Zÿa£Ôû ¡ÿ!˜WBÒR¡5C’{n§Ióg“‡§Tğ<BAïašøÓÄÿMêÏÒ¤áuš4ş–&M¿—¥äØH²²€&-•4¹j	M®öĞ¤u%MÖ¬§ÉÚ4Y·›&ÁM6ÜI“¶?§IûÃ4Ùø8M:¢Éæc4é<M“-¯Ğäš_Ğ¤ëMšÔÿ7¹øV´{u^ñ›J¬É+†‹s	×HMŞ­¦ÉWü4	­¢I×6št§i²tr¹@ˆE,£ƒ:‡&¡œŒö
¤ê¼¬´Ûºè%•lÛ@‰k	±+G˜“cÛNaì€Ò}„¸Lg*8/gî8Fª&ÈØ”¡\aÿyóËÉM+ÿ&.InÉ-¤JÒÒçIéO°¸Å¤`Iea^”ê!‘w(¥DOn¹MvÌ•¡…¸Íy#ÀE‰QK–H'c¡İNYz1‹İü”pÚ:íù‚=š£¢ö™.:D)ŠÊ«rà—kü‹m·«	úÒv£k²3R/àhXêh:Gæë;Àï\ıãú‚,‘Mµ¨·Í¹Ô¥gµVs§†Ş ewiÙ5ŞÕšø5šÜµoPËŞ¡eG\×ÀXtzÊd_ê
+ˆW¾Ùµ•N¿KºÎF¹Ğ®	è×
£Zv·–½IãíĞ´lÖÄwj¼[µìZv/íåüwKó¯<Š½zi~í	šœ&3¹şåE\g”ì ë]%;æ*ƒ>šéqµçB6îšè¬
—háÑò^œ£¹ºÙUP­ZRXZ”»g–ÙHr…2~Ö’©|-]^6
Õ
ZEÑc üj¬¯ÆrhTh™ÂW@ù~…ù6³<Ë§ªA@B‘°dV‰Í:«°lÎ¬íeExäYVÖYÍNâĞ¬dÕ^‚	gKE»ì.k© cgœN™-w¦Âf»º¢¥Â‡ä¹AHKÅÕ°ÛP{I ×œâ1æP…`Â©
q69I|á”E„qİ™Dîf·pgë,}!n¸k/QĞB£¼¾˜°ÉÅ.,Yiv‰É­,µ#ÂXuÎ^³]*/&Êc|•Ó‰³åÔºŠ ÚPb)Ç~²DP7§LÍÎÂUµ 3×azàt®ÂÙùäî‰K©”…4Y¸—bÏ·†R‹KÀ°%%ˆ$K›Uû®p£"¡8·µ\6Œ´µÚ-ÈPo	nóÌTcC–rÒËäF,ÓŠIÙrE æĞ¾Bg,dë³ÿ„?Ìš‰5H¨Ë¤’u±hO]8\7ÚÔ 5j“‘ŞPº6gFëî&w}Û­ıƒZ]xùr(5«×M§ĞE‘~Ñ$ÉB FnTGuá”ÏW_ôUqR“è¡¯–êüîz·G­rQšÓéÉôL‘[ˆ0K8ï‹ö»È­	¥ƒÑ°4’HöÊ >K=¡y¨b¡=ãe„BIcïG†ÒÑD\J'eN|\Æ6ËÅº36Z‚İ8İ5gó(ŒÃr…0•M”4!ƒÒIµ”Š¤pÖN,!£Kyœ“ƒfXçe=[…Ã.æÙõ™ı–U‚c£%Íœ"[¹Íã8jó½aC;mVÇi‹3Svò([û-lüä§ƒhQ“››%ÉĞ'èŒ_=ó#²XCù½MœtUE£‰h<šFïã“¤şxF
R‡ËÑÁ\‚bDê%zB1i8””(ÿ}9
¿,–\wYõ-8®hgb1l¢”FdK‹ïß‡ódcŠóƒ¡QLœ•¤¾P*İ„i²	Í(€·#ë!¥dëİ“HÄĞQ¨HE÷FpÙAöá•F¯ë$Rd#9B4";L|K“¡8á$K^,ï3ñT´?é%OMĞĞGë’íe!%dSß	ÇÈ¨†¶Õ J¹9R,‚Ò’]íúö zI6¥!@$X¹?Èª‹õF‡qloR‰dV¯ÉZ)K—k‘íš: –èõRcôÎöàÓzštÊ	¥“píŞh_‘@ôÊjËÆÑf>¬ïuª—ì\İB¶
$ı­®{)ç+£©!È<ä‘s§´Z›úˆìë@,‰œqİÜlæ»AÕIr+
ô½@ÛBöïTr”a¥Êú&ËÈyLë«§­ åë+Ğf‘9êˆ [=µ—ä{˜£7ˆÈIç*ndo†½Õc¥Ôúßëº—*ığÈÓå½BÚÊ”SfrQG/G’)Üu"uø¢ÑwÕ$#u#¡>y©¨ŠÕÅjåecO&’"}ªJ¤{}’Ç×(áU$”#O ¾…–Õîñ5RW¡zÅ¡#©[JFúÂ‰î"ÒM†€Scñp¤W‰¦$ê†åIİN„ÜBK;»ÓMªdì‰¨0	»¡X+°7O
õÈw8Òáˆõ•ÒfèÙ	§Ã±³³;í­g*zır–êíÅm#5?½º^®Œ;‘kAªošº~®¼\gL<’æv§eQ¨;Øµ©Û#¡ÄP$‰WéäUÓ®·…T»åSô` 5
v‘ê$7Í¶‡‡{p»3E:h¦WÓç!‹YHÇCºŒt¢	L7 Øqô%Pï†ÑL"­-ÉÈ ã¤ö-uøäñ<¢Oä5?lRˆêòŒUkKµŞik9X³ôk­²”ë 8ZÙû(]ñzŠcĞ;>ÃâhpåÇcpbF'e\¢Œ¾_uUêªÅø+°—q›êŠ«úøÉ+³êæ~Ü¸[0®bFÿmôïŒãeÖ]fEÓ<°¶†k›&Ø„hË¬¼6ÁB«¬ót„hÎm…Ò6&êra¾Ó¨µ>2ˆ7tlY³ºC’R™©]28ûô@ôb?”§Ï³o{«°í99GŸi«dÛ15wÔÀ2ü¨í¶îz¡_î‚ù·«òÎ=vşüyòì[™.eøô«l¹÷v!a´P˜“ŸgŸÀ{N|´EsuO+ĞêY…wXÖÎ$û^RÖ¤{fÁ–mÓ=§`Ë†tÏ'ôeÈ]wÈMî‰J&CcÈM§§êéIF†‘;M#w818ÁÃ×İ“JA™m(ÓC,Hß@<.ú	$Sø ¥D›¼œIg†¨órÇéˆ{CçöZÌ¾ÉÀ€Ïw "R_«TÄÇaäN`-éPÎ)éØ M{CéĞÅG¢|fG¹Ş
)ûÙu!C¿õ­ÎûD‡}BäÛ/P_˜¢ş×MxôõsòŒ8Ë{çİÎ­‹`Ê8á¹6ğÙ•3$¤ÅıiĞ[e¹°ş§9õÍÓ—§¨˜cÿ Ü8åİd%¼[bíïäèÿJ¾œGÖßÎÑÿ`QO%¼Êbõ¯àè_8SNïµ^X€£ÿ°‰~§‰ş= “}‡û=è¥¹æú•ô§û»ÌÇ?Ë¢~ëõoä´ÿ´B×ş“öàÌÿÂ29½~ŠùÿUşÉú‹LôçÂë¾IóôÛÜnÒfúÏy&ßÿıK9÷ô»Ğ…ïÿ£œû÷µ²éİÿ€1ÓM@ı»¦hÿyï¦½0uí/3iÿ¿›ô=-†?Laÿ™ØNë‹Ğ?P8Şµ²úÍÑd¡œœB?ïz‚öË»çYüjoÚªßOàkŒÊ¶NÒsğëßÀ¨9ÖXM{„àVÃÁs9xŸÁÁ|&ŸÅÁ8x/áà³9¸‹ƒ—™Î£bü[ÔïÁ_ëîK•nü›ákM|‚bfxŒƒåàü£çä9´7)päÌ:¯9¾ÖË
ğªçh|p5}zcvŠ¹À¡ŸsS	i ï%1WÊHt(Ÿ¤À•¯Ãõ£©˜Á•;îÒáúà*~˜şh/`îh?ƒïú*ÿ1Ğk|/Ğ\9CmeğÛ€ŞÅà½›#gŒÁ•sÛİCöƒ{ ˆÁçşmÿ³¾
ğbğ!ÀÏ°ıøËş=À_eğgÁø{;Á/åàWpğfÏ×¼ŠÁ›ßÎàë ¿Ã?Äà{ ¿…ÁoüOü0àÁàOşƒ¿øß2øÛ€?ÉànXrN2¸ø_fğµÀÿÿ9àÏYŒx
>Y8Ãà{•O¬Fü~¸ße~Ÿ2ßüiåÛL«æ÷õ«ßUÿ+€odğŸ+ëƒ¿¡œ—üw€0ø›Ê<eğ•sƒ[¡Ÿ`ğw ?Áà›ş)ƒwı*ƒ‡€şOßô9Ös9E¼œÁS€Ïcğ;_Êà_ÜÏà oåÈédğ	À»ü;€§ü9Àoağ§ gğÓ€O0¸r?¾Åàï ş]ğ§üÿGÿ2OÜô¿0øL _eğÙ@Ÿcğ@¿Çàn ?fğ•@Ï°ñ6ÀK|;àó<ø2ßx=ƒï¼•Áï|ƒÿà]~ğ]şà½şà	ğ½ş3À0ø)Àïeğ×€Áßü›®Ü'<è#^	ô^ôO¼ècğõ@¿ÁŞ_ ßfp	è<
tY®¿ğ…~7àµ~ğ&ğµş8àşà×1ø³€ÇüIÀÇ\éß¯åjë‘~ßÿ†ÿEàÿk¿MÇÿÃÿ+(<Îà@¿ÈÈQÎ?ÿÁá‡±SÙ¿~Ìğ¿zïµ˜·ë)‹¹ıús}¸şüVhò\CÁ×2Ï›X½å^§{mÖŞj¿^gŸÙ¾¢D÷u?ÑõÑyùªĞñëBĞ"œZ>G‡7èäWêä#ı¢_ßo-:\ß?;\©ŸfälE_âÿ—RÇñ?şz?ÿã	4fã/Ë5İøŸÑJöV+š‡g}_zà-ò8ºíà¾s'ƒiïLî;«dN)™#ü×©ƒGÚn>ÕvpûÙ¶ñíçÚÆ7¿Ó6TE` xX&îÙwxüÄ9¦úøI¾èñàãªI˜xTóè'ó Ú LL(b&>©˜»ÔîÀÄ­Š˜[¹bV‘©?Å®lİøóm~Dz|×È§ÊÆSeã©²ñTÙxªl<ÕçOeF<Õ~AA‹lt|ÕXÑ?:Q”[%Ní0Pm:ÊzèÈ~Ôb¯²qUÿÏâª”æÊ]P ÁU2DÂ«&ÅS£ñTcÙxªl<ÕeŒ§2üQ½OKå²Yöë,­¥›6uØæLØ¬o‰mÎ)óÌ¢RK	–ğ úÑH>nÊïˆç†VM
¡"±YÄìKF•Ÿ£Ê†QeÃ¨¾haTªËÊ†PeC¨²!TÙªlÕ—3„Šnâ˜/Uç÷¢¸Åı(¸(ï.a¼”ñoş"ãŸôEÆ¿Ø‹ŒWpiâ¬È³}©³Mÿí³>–Š¾h›"Jyúãªr'$%…^·÷³»%èÂñUû…ÇWˆœw%£KÕ£é5ô°ß×ÿ2Ïzó!=«+€Ìã³”úSÅg=Äùf_©Ÿ?E|Ö×yí¯1~€<ŞM7>ëE`œ=E|ÕQNı×àÃ·¦ßej?ü§!Ê»ã¹`;k7GÿKğ±õ7¦ˆèäè¼Ş¨g.ó­†‚¯âèÂ;¥©â³Vpô?o¢?ßDÿ02Ïy^^åMŸõ¯û?šf|ÎÀõ[§¨æ´ÿ,´B×şB“ößÁóåZ¼Ã…üÇş†Éú‹MôÓ8ñ1õÿ²Üøı	¯ÿyñ]gËßı°ßéå™ÙÿaÃäñc_´œ3~~YnŒGàÙÿ7œûÿAùôÆÏdßõ!Ôš¢ı'8í/l„ÍŠ®ı&íÿ%2¯€—
„ÛÿßÈ<¾ëÃÆï²« /YıorôW/‘Ó-Sèç]ßFæñ]P{‹'Åw%©ìœIz ¿şú”ßõIã¸lœÇeçàÏÁ?iW!/æà¥œßUÆÁË9xÅ$ìIdŒãÚ/˜O¨\98‰ÿ0ÃÿÃïãà•üznåè=ÃápğcèSÄ›}Æğ²İé ùE>{ ™zÌ“Ï€Ø‚D,ŒcÎˆàXª½;íõ’#·„•Ñtª=vaÌ­†%xÃÒŞ&»ë¥­›Â²äÿ5iO¯î6i›×nTK¶®ïêNtKA¤Xö;P‘ƒ×ppoÒù£*İm\£Ã‹˜ı„"g¾NÎ/Óá7s¾3= “?O'ÿ ¿BÇ?ÇÎ‡;Ïò]ÿÀ±ó8ÇÎS;_áØù3o0v*²ŞåØù1ÇÎ‚¹‚¹ss;æv.Œv*ß7	ævs;·rì¼–cgÇÎË÷©Ø4İ¸Ï(ĞlÜ§ÊÆ}ş™_
>4÷ùĞlÜç~ Ù¸Oå<¶ûÿÚ»àªŠ3¼÷œsCbğ’hF£€¹XPBˆˆu¸7¼nh€ ¡Ò
ĞÜ`pÂäPµuL‘B­:ŒhM«âTñÑêÔG!DëcDÇZœÖzÇ×$ˆ#QIw÷ü»wwïùP°´eÈŞıÏş»{öìÙİ³»ß÷#é˜¸Ï§!lâ>³Üçx÷Yˆà>Ç#¸Ïiî³Á}®EpŸ ¸ÏÇÜçûîs<‚ûà>Ç#¸Ïñî3Á}–!¸Ï‚û,CpŸîó÷ù‚û|Á}¾…à>?DpŸcÜçñùt÷¹Á}6!¸ÏµîSà;MÜçñ¾òG‰ş}1îs¯˜ïò}b>fÈSâ;È‹viâ>?ï©!?r÷)>LLÜç÷Yà> ¸Ïåî³Á}.@pŸËÜç
÷Ù„à>;Üç:÷y-‚ûì@pŸ7#¸ÏûÜçÓîóa÷ù,‚û|	Á}@pŸ)÷ù9‚ûüÁ}†Üg‚ûÌGpŸÃÜçX÷y!‚ûœ‰à>"¸OÁ}6"¸Ï«Üçõîs+‚ûÜˆà>CpŸ÷ ¸Ï§Üçîs7‚û|Á}@pŸ‡Üg6‚û<Á}DpŸ“Üg9‚û\ˆà>/CpŸuî³Á}Şˆà>7"¸ÏÛÜç½îó÷ù8‚û|Á}î8FÜçóà>3âÿ.î4ä_€üC~äoò„rÂ‡<hÖ =ş»şMôá“*Ö…¢Äÿ~¿	t(ñÇƒSât„"Wñ Qrbñ ÿK¸O¹-ÍñŸ'6†ò¼ÛxöÃN)óÁ–L)	ğŸß†ü§[€ÿ|0;¦íÃ-­VöÈÈT’Cÿ¤oZ¼1y-¦ù‡ iágË5hoÿe*ôwS­˜æSö_Ìı#}Õ?¦ù•°4_)—è£R•µ…º‡×hş½P”­ëY ×z=_øy '|qü¯y5Ü—ğ£F#v8ªŞoå†ƒ†‰ı÷Á1ÍOB¼¤¡·êeÃs}Û"È«ñ½³ôçÀ  e¥4$½ÓÿÖM-›PVZÜÒT\ÂË”qçÌ_¢ÕcTyşXïÊ5ÖºD|±G†øY$Íµj®›anƒ²vfŞÔG^„ÈÏ
ù§SƒÈ#òUPGÅ4ùd$ßÛò/@â_Ç×7I{Ú§xïò¼é§Œòú|[Z“µãÆ±gZÆN³56­vùÑ!×%îÜµî¢º+Vµ´Ö5Ï`H’ºâVTÏs“uÍ ®7£¡iu]õŠŸ°=vÍÿ
º}"wEÒÛ'ÁÎ¶­Cë«Ñ«*úëŠÚZ·……&±P­¨BuwÇe >ù¬#rÖ6*ˆ2§²¢|†[R\R<Åû½t©;¹¸”È]d‹ïZ¶ø?ï}‘ŠPº½·½*‡½M›äzuH›#¶¹%›éoıvQœgªûÕ¢}…•½`>_ù cÏ9ªÈÕtF+ru—w¢"Wûû©Š\íïbŠ\&¹Ú_T)ru—w©"Wû¤DÇìÄ†ğ³…Q’¸¡»5Ü3™wg´î}S£QúFı‘şR£¿X˜£{Slâ9êfUÓ»—‡ÇÂ¬Jz»yøfİ]ï#<|³ªéíâá_°0«’ŞÍ<üsfUÑÛÎÃ?eaVüŞ5<ÜÌÂ¬Ëì­¡ÁôyÍ[GÀH¶Ygİ!:¤Ävq!ñÔ¾\OÖ³–Fğ¼æ¢™êyĞ-"ı³Œô·d¦ÆÑ¤?é£ŠÎW/Ot¾“èxï`UuÅsİİT?ñÜÎ*î=×•#=Ïéëû4­¾ùOMô.IL¨§^¢ãP„&w•µ|—Ç§@ä§Ëw°K}©!Eí| ^‰¿óÍÍÛş%±sÿôDhoâÕCmTù)Où5ªœèÜãé¿úí—\Ä(zÛòyÁÆ
¾'|…>ÙÅÚC¢ã’ú¡õY„‚%;Rt´¥ñûö.ï½šmz‘ŞÏGø5êBÀ¯±,ü‹CÀ¯1—ıØ!ŞÏÄöT2Ê¯ñäWôù~¶Îüq&ß.FEq7“(I,’füÍ^2¿£~Ã_šÉ,5’9’NfKÏ8/_ã7Dòkü!#™|#™SËdnêyïKŒÇ¯q)‘üÉ¼@%(¿Ææc´o¼9~i¼³/şÃŠÎÏâK*:ÿ¯®Ü8jéiQoã„zê/®óş¤$v~e³¥ç¾/¨æµ#leçşÊÎÏfÒ4ú
ş™èØJ\ôaÛ~ÖÑ\¶<¾,¾<~yÜİµ9İÀ?Ùµr3ï› +
§Š¾É!êĞPûâèßKiAbûÃÔ?ÀÖÁh­±¶RJıJê_Oı‡¨¿‰úŒ»üzúpÇªC«†í}¤şÍ,>õ_¢ş½Ô/°Òç°CÚ9ìAy0÷Ï¥éUîÇ?¾G¡Àâ·îëëb"y³#…s‡ä^•İN¦Ÿ}ñØÉ#ÏUõÍsßÃ@?EõÍsßâ;„­¬¡å1Ï~‹ëËèÿƒT?Ñ¿f€ôÙçfZoÃ‘ëÏÀõ!ÈuÆÅ¹É&+?-wÕ¯ãµ‘¼MÖ¬Há/íY‘èFgVdôÍáDdâY‰ÈÔAó"±†ÈÔxdb<2º<-Òøå‘l^×Ótn¢éX$p\à¸À.p\à¸À}nMNŒû1Ø¯í¿
äÂ…’7¾ØWÀqV¼Yà‹!<VÒÄZùnXËç7Ä>¢àèVíÆ1·®‹}^uÿ”¹u–—Ø(t¼°X×x®‹ó%÷CùrüLäTz›×Ë_¬eˆs­bHì%¼JUVL“G!,Ê-Î,äùéëãÛ©°¿Â"ßƒîÇ¾Õö#ö±M·ëZğoÿvğ·ÿø{Àü”ıÄ93fL‹3É˜(§‹–Lœ4ebYÉäèèEuÉhbE«'Ÿ0iÒ¾†“™Øl;/+³‰Ê2è®iÓ$ËZÚµøiÎ—Œ»ø˜İô‰¹ƒLé7ÿ·Æb…qHßO‡ôoÙ_v!Ì–/9‡4ÃˆHi´–Ò,ŠÂ!½•ÒoÎ!Í^BÆ!Í‡Ki&48¤Ù!q¶æ.£¡+C*‡tİ29¤yb’Cš‡ti.Ò9¤¹Hç~^ø,äÏ!mÁ¥Lé	–Ê!ı}j°28¤™Á«»,“CúA*ÙoùsHoyÒl]ÖŸCúûÿ‘CºÉIsH¯u‡4ÃYÑ3_³9‡ô6Ëä¤œCš
–ÒlIãî&
‡4Ãœ+ÒÌ$’Á!}»Í9¤_&8‡4ÛdñåfÜÖ‡ô[á.°UiÖ–€CšÅ’Ò¶Ê!]Èc<¥xÊ4Ûã¾ÀV8¤Km…CšÅHsH3KgËì8¤Ù7pH¯´%‡t³Í9¤×ÛÒwÚœCz“-9¤™¡©ÜQg²†Ò·:’Cúï¶äfº€Cú#[rHaKivò8¤12pHr$‡t©#9¤g8’Cš&€Cz™#9¤·ÚœCz£-9¤³9‡ô=¶äfo.pH¿aséİ¶ä~Û–Ò
Ò‡mÉ!íHé3É!=Ò‘ÒÒåäfxà¾ÌáÒuÎ Ò?w$‡ôuänw$‡4ÃB‡ôGrH3‹RÀ!}§ãÃ!}‹#9¤·9>ÒaæàqH?ìxÒ]0Ÿõ8¤Ÿu4éw•Cú}5”èq4é4‡´˜3{Ò/8|ÖËÇBÆ^#ÆÂHØc£aca,ƒ±0•±pK0ca0÷±0ÌÇÂªl¿±0
k,Ã¹t;MŒõLÓ½oİĞ°×éøñ†ğxïĞxóÌ8ãº´1°Ï	ì(v|í(â;Ğ(’§Ó{C#	óöà=ˆ±éËìÚ¸ÀÈF`dãä4²!¾0²!>&¿–‘y[¿6hëA[ÿÛºÌKkïb~8@{ÆÂğÄS
—¼&?¦-ÿ¯–E#øî·g¾–¶úp¶À¼Ã1Yvl9¶üm9œXınøÚBæÒ–N¤É|³„5
]Iëf[ëWµv«»Uİª“Än•÷.Š£Á»¼‹Á»øßzÅ§ödqğ¾©‹rõ‰?Èö?Ğ&>]~¾øFY«d|ÑOÛ—‘öf¤ZÎºæ5`Î&^^1¡uÅ¤¸~EK=)N®_M=Ÿ™Å¡“bøúÑ®0™C#Â¯5­„[ğ!`¨g%Ë6DšÅqë“ÍD1’£Úüaâ÷•µÍ¼+h£¥YÓy'ûãåâ¥ÈíÿHk@¦¹ÕpnKHµØ£X 2i¦‚Â1Ş~ÁÏ£Ë-Ék£Ëmy~S—;òÜ¦.Ëóº<Ë÷\$ãùOùÊ³å¹L]#ÏoêòSä9V]Kª|åƒeó×å§Êó¯º<BöúÊ‡H^]GÚ}åùò<­.?M£Õå§“”¯¼À÷Ü'³/ ø>tùòœ¬.?“ÔøÊÓü3ºü,¤]È‡"òaˆ|8"?‘!òh†Ìã"Ê´‹qŠwú“¨gI˜;—ëqVL·†øê)~FI¿âw!éoAÒWwù9q$ı«¹nf;¹	ÒIİï] Ï3Î—?"ò5ä{ œ›rzöƒ2Ûí—Î#ln/'³ıc÷u>ŸG=)!ÿû%H:q?³ı_Êo$?£üõ 7Ëy5O'ó½cXú¨Ï{´	ákÚÆåƒI7ô'âüø 7‡Ë?‡üy¢^Bä)Nf?öR\Ë_>‘Ï´üù¯VYşå¹Iç‹Õrº_x7-¯Ô=ræö#é;ìD‡OıçSy¾u&©7äìÓÀ_«”Ç}F½Åm¯<U ¯ùBo!Ié/·ıË¿âwĞã·Øşõó+ÛŸ×ëM¸_3ßä«`îs«çï8Ë}ÆM¹ì‚-Ç•]m¦¿5šÚæÖ–Ö¶•+‹kiJsg,r++W».Ió¹­n-ãk!>"×M6‰Ü“­MÍ-îŠ¶u„Î¹Ö4ÔµÖ%‹Ë&—–úGrÓs9—ÎÏš×oö—lkl\OU”›BT×½(>o–;kşLÆ¦ÆK¿áfÌ½xVµ[/¯œåò%‰¤.à,bÄù£ùñy3›<
™àN‹ÅTÚ0`«miãwADì£ yóâû“ ùf’¦8ƒË@c¦Ò¡Wü)áŒÔûc›ûz<qfø>Äj·­¥.éc¶§´sÕ'àÒkâÙ
N;³¢Të<éGïı
H?Mcõ’7ƒ¢ÎHüksßéÔñot­Û[‚åE>n(Ñí»¥ùA‰†3ñmÂ}è\sişMÀmeŒıº›˜3ËÀ¡­A¥¡gâÖ.„¹šeàÔ°#&şöE§FÍ2poÂnÀıØw›3¡/¾ŸºÃzı‰òZ†_˜5ßY)Ğ½¾¨#“{ZØg´œ\4KÇÉ™õ'î¿®•¸»ª,§ç@=›úWİ¾£§FÒñ‡Øóo6ôÅw`èwñóÿZC_Ì÷‚şë¶¿¾p†¾˜íÎÕñ…Xù;÷GÌ“öæêí—õ/ç†~š‡Ö'ÈÿnC_|Ï¶NÏ?ûËÿ÷D·o™æ¥ÕŸ3¦ÿ8Ìalgºo¸|3¼“èö}Å÷Bê(õ÷À³³œ¥à|ÁaC_´ƒWŒüÅwù¡¢şóşë†¾ü~¯f ı·}1?®‰ú?o3ü.Ñí‹ùrô£Æó7ûãâo_Tè—#ı¿ğÿMüm^nıËè?C!}ç\xN‘şõOEôà†Jœşõ‡"ú³ÁlûÓáşõÏù×_hÔw¸ÿú+Aò1Ş¿ìK—#úÍ†ö0ÀøOüí›>9[?ÑçGüí«æa×Xvz0ÍgüÈAò¯‚g€ç¸À.p\à¸À.p\àw²¸ÿ ƒî‹L ğ  