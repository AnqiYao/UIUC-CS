#!/bin/sh
# This script was generated using Makeself 2.3.0

ORIG_UMASK=`umask`
if test "n" = n; then
    umask 077
fi

CRCsum="1837613077"
MD5="53bff08d0a3d6d5b66f8d1fd260defdd"
TMPROOT=${TMPDIR:=/tmp}
USER_PWD="$PWD"; export USER_PWD

label="Extracting potd-55"
script="echo"
scriptargs="The initial files can be found in the newly created directory: potd-55"
licensetxt=""
helpheader=''
targetdir="potd-q55"
filesizes="2149"
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
	echo Uncompressed size: 26 KB
	echo Compression: gzip
	echo Date of packaging: Thu Apr 20 01:34:58 CDT 2017
	echo Built with Makeself version 2.3.0 on msys
	echo Build command was: "makeself/makeself.sh \\
    \"--notemp\" \\
    \"..\..\questions\potd2_055_heap\potd-q55\" \\
    \"potd-55.sh\" \\
    \"Extracting potd-55\" \\
    \"echo\" \\
    \"The initial files can be found in the newly created directory: potd-55\""
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
	echo archdirname=\"potd-q55\"
	echo KEEP=y
	echo NOOVERWRITE=n
	echo COMPRESS=gzip
	echo filesizes=\"$filesizes\"
	echo CRCsum=\"$CRCsum\"
	echo MD5sum=\"$MD5\"
	echo OLDUSIZE=26
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
	MS_Printf "About to extract 26 KB in $tmpdir ... Proceed ? [Y/n] "
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
        if test "$leftspace" -lt 26; then
            echo
            echo "Not enough space left in "`dirname $tmpdir`" ($leftspace KB) to decompress $0 (26 KB)" >&2
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
‹ ”VøXíZ{oÛ6÷¿3àïpK‹ÖNbGrbS£Y“­Ò°víPt…"Ó–V½ Éy¬ÈwßEI”,'é#1ĞòĞÔ&uo’§ã/ém5n4¤Ñ`ĞĞ†š>èüSÓt>/¨¡ok£¡6è†È‡ÜÃQ; yœ˜@ã9aWñ=|Öøş¨·e33ìYax»ë?ÜÙYºş}­Oë?ŒúCm»ßĞt]í4@SëëtÏñ-w>a°gyfb[Íyìø3ğMÅ¡i1ˆ“Én«™ó­=sü'´eìµV³Õ<eVD{ŸŒÁ5ãä˜2·-x€öV§ÕüÔjÒÖüÌ#°Ôc³ˆµš—­fCÑJÏ¿g:şJÏ?ÎmWÏ_©ó·çßtgAä$¶7–NûÄIÄÌòdzèÇ¥ª`çUaY­¨¯,2ö.âìX.^ÇÛ‰6i»Ó¹o%NàC@Ââ.²zÒ£Ò‚l`Ù¦?ãbş,3&®ìÌ‰m^v6SøoD©ŠàÌ‡yŒZ^ºÌD£~0^¯VgëÒ$œ0â›p…$=‹Ì	ê‘ÃX…£rÉ{ŒéK(p“—Ãt^.›Ìe^ûğigtm¶ñçüÑi øş7Ğ´ËİT:+¯Ş}´¹‚O¥°ù2BÍU›V0O`oÖR1ÖhÄü‰+Ô¦ó½„Û%}¯0×¤çÊôã3-Æ™›>ÇdQ,Å« UÚÙ­øğÊf\ “JfÄªŞPvÛ±óû€ƒ*µ]üØ+¬ôèº‰³TF6‘3¾sŞÓø!<¬8!Œ+e3ë#…iQ„ù,k–ë<Ä›ĞŠIkâL¡]<Ú/Ì×¸¶Æ_ƒ8qÌ··WÍ scv½0EñT,bÉ<ò1sË_´½­gæG6u\¶²ú¯ÒşúÿmMõ¿¯êÿ]ĞÑÛ£çÏp3Såj5_üúÇŸbĞxñÀ¬¸Yåé´Å¿}‹¬–‹õvcƒ;>øÄ»XÚ÷­íºtgĞ}¡A÷‰E´û†'‘ÙjÊÂÇ‡‹²dE¸ßnvhªÑr§ºß>>ìÀı€¾p]èpÿ‰¤áõ:œıE=àßR	âMc6 {]Å›'ÆÈstD–@#Ïå5Vß@näAw
ë¸rB¾¶ÿ“_ÍùßÙÑ†Õşo¨«ûßİö¥.ßÙ†!¾´­ÀÇ~K~>£¢Û¡Èñ§xˆı¹Ç"Çúà:“Äœß0<ó¼İÉßmÌc~÷Âyl81­m”\xêø1‹’v>Æ×[»³)÷NØŒº­|ÌŸf:Næ;á®wÒ÷_MPßØunä4p&[’¼Èma3Œ8ã‘Àè›P–óÏ¨diêÓ k¬QÍr¦‡ØÎ¶Óˆ&ì¼¤ËüYbcœ¹ÑGÉ,Óä±~?%qdíÃzªJbŠœ™½„‹¢È{ê‹*
ÇûÂ©5J[•]jÃRØÙ˜¼‰Êñîú<³–ù#u_" wüö|yˆïÊ¼ïÀ§Â²¤³Ì&‚½”m´«aï-†òàäK¦½äNEÉûÎ2‡*ŒuåÜ?‹œ”ta:}†)Ş—â³ì"e3a^(m‘·İ‚©šQ‰7«½zŸ‘xäš±uŠ¸–ïé×aíÆ8b!ú‹ÛIŞ;!Ş1ü¤´}`úõ[Hb.­œ³¸ê2)‹×%¨¤şóV >Ÿ˜IçÕ	5•üöÙÙ_¦;gŸU"jê_®G°^‰Ó‘•+RŸ;2ök³äˆ;KnÄLÚúñ ZÀoPÛh™ºÕêÄ¥Æ —Öµ´ zí¢è¥ÅzºPËÜCwÓdu–½S=ß"a}±÷ôJşäm,Â_í¹*İ8ß­I³ü^Î"
ëÙ¥<Çx—•nÜùvæWòµM5_.šÎª!Q–¹Š÷Õ[ó%¿7ËqÀ"÷Aı¿½ªû¤/üş§?PøïõÿS|cLáÙÁÛ'G/?<i5ïáØñYiêJ<x-m¿eäw	šœöÔãåP°åšqœ•8QÓÂù‰ëX†€éÖ×Ó/ëğ(«	Š‹!±Õ66cáb|Ì¯ñBd«|%(ª³!‹°ôy±\³!hqŒth/ï@2} gæLHn™gTàë›ø«|.º÷:¼™säSáà<¼‰k¥^¬Ö±üÚcäX;éÍ§ßzğ4Å@ÑlTÏl†Y¥ÆDB®É³àä_\6ÎÉoB“:ÿÊw¾·Ó›2šÓêék“tÑ;.Íy:sNÑ±™²ûeÙânÆuNyarQX¯º‚­gÈÊr½Íú¬§é'W–E€Ÿ,Cj²W×ÖÚ¡ÆÍİIº°§ÄÁ”Ä™3áÃ$³'|_Áa€gÕ’bq½`‚ÛjÙÖã}›Ô+Öû„_ì&j‚²^pÊâÂ)')¶Ã2¯‚eKÁ›3<•ôZÏÕ˜Q„ -geçª*EKRêñ¨La†öyx¹“jô¿ÿrEøßöP_Äÿş×ø_éwµbdâË7ÁÿâZ)şWê».]Ò2K_ÿ-QüİC}s¨o|C¨¯ĞyPŸĞ^rç¨¯pè&P_Æ}ÇP_W-Ô—}5Ô'Øê‘©Ê^!Ô7ş> ¾,¡+‡ú2G¾êËÅP¨/_A}
ê»-ü/ëûVˆÿí(üoÕøßÓçø_1õú•`º)¨À»B ÅßÔ~xıİøkÀZ¤.¿º*P!€„ UZu3Š)R¤H‘"EŠ)R¤H‘"EŠ)R¤H‘"¢ÿÂ(ú P  