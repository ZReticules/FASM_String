macro init@cstr name, lendata, bytes{
    local numbyte, nowval
    numbyte = 0
    if name relativeto 0
        while numbyte < lendata
            load nowval from bytes:numbyte
            store byte nowval at name + numbyte
            numbyte = numbyte + 1
        end while
    else
        local ..pausevirt
        ..pausevirt: end virtual
        while numbyte < (lendata - lendata mod 4)
            load nowval dword from bytes:numbyte
            mov dword[name + numbyte], nowval
            numbyte = numbyte + 4
        end while
        if lendata mod 4 <> 0
            load nowval word from bytes:numbyte
            mov word[name + numbyte], nowval
            numbyte = numbyte + 2
        end if
        if lendata mod 2 <> 0
            load nowval byte from bytes:numbyte
            mov byte[name + numbyte], nowval
            numbyte = numbyte + 1
        end if
        virtual at ..pausevirt
    end if
}

FSTR_MINUS_FLAG equ 1
FSTR_PLUS_FLAG equ 10b
FSTR_ZERO_FLAG equ 100b
FSTR_SPACE_FLAG equ 1000b

FSTR_HAS_FLAGS equ 00010000b
FSTR_HAS_WIDTH equ 00100000b
FSTR_HAS_PRECISION equ 01000000b

macro fstr [args]{
    common
    local lendata, bytenow, smb, num
    forward
    local ..base, ..unformatData, ..start, ..end, lendata, bytenow, smb, num, ..end_format
    ; define no@local
    virtual at 0
        ..unformatData::
        ..start:
        db args
        ..end:
        lendata = ..end - ..start
    end virtual
    ; purge no@local
    ; dd $-..end_format
    bytenow = 0
    while bytenow < lendata
        load smb byte from ..unformatData:bytenow
        bytenow = bytenow + 1
        if smb = '\'
            load smb byte from ..unformatData:bytenow
            bytenow = bytenow + 1
            if smb = 'a'
                smb = 07h
            else if smb = 'b'
                smb = 08h
            else if smb = 'e'
                smb = 1Bh
            else if smb = 'f'
                smb = 0Ch
            else if smb = 'n'
                smb = 0Ah
            else if smb = 'r'
                smb = 0Dh
            else if smb = 't'
                smb = 09h
            else if smb = 'e'
                smb = 1Bh
            else if smb = 'v'
                smb = 0Bh
            else if smb = '\' | smb = '?' | smb = '"' | smb = "'"
                ;smb = smb
            else if smb = 'x'
                load smb byte from ..unformatData:bytenow
                bytenow = bytenow + 1
                if smb >= 'a' & smb <= 'f'
                    smb = (smb and 0DFh)
                end if
                smb = smb - 0x30
                if smb > 09h
                    smb = smb - 7
                end if
                num = smb
                if bytenow < lendata
                    load smb byte from ..unformatData:bytenow
                    if (smb >= '0' & smb <='9') | smb >= 'A' & smb <= 'F' | smb >= 'a' & smb <= 'f'
                        if smb >= 'a' & smb <= 'f'
                            smb = (smb and 0DFh)
                        end if
                        smb = smb - 30h
                        if smb > 09h
                            smb = smb - 7
                        end if
                        num = num shl 4 + smb
                        bytenow = bytenow + 1
                    end if
                end if
                smb = num
            else if smb < '8'
                num = smb - 30h
                if bytenow < lendata
                    load smb byte from ..unformatData:bytenow
                    if smb < '8'
                        bytenow = bytenow + 1
                        num = num shl 3 + (smb - 30h)
                        if bytenow < lendata
                            load smb byte from ..unformatData:bytenow
                            if smb < '8' & num < 255
                                bytenow = bytenow + 1
                                num = num shl 3 + (smb - 30h)
                            end if
                        end if
                    end if
                end if
                smb = num
            else
                display "Unknown sequence"
                err
            end if
        else if smb = '%'
            load smb byte from ..unformatData:bytenow
            bytenow = bytenow + 1
            local _flags, flags, width, precision, type

            _flags = 0
            flags = 0
            while 1
                if smb = "-"
                    flags = flags or FSTR_MINUS_FLAG
                else if smb = "+"
                    flags = flags or FSTR_PLUS_FLAG
                else if smb = "0"
                    flags = flags or FSTR_ZERO_FLAG
                else if smb = " "
                    flags = flags or FSTR_SPACE_FLAG
                else
                    break
                end if
                _flags = _flags or 0001b
                load smb byte from ..unformatData:bytenow
                bytenow = bytenow + 1
            end while

            width = 0
            if smb = "*"
                width = -2
                load smb byte from ..unformatData:bytenow
                bytenow = bytenow + 1
            else
                while smb <= "9" & smb >= "0"
                    width = width * 10 + (smb - 0x30)
                    load smb byte from ..unformatData:bytenow
                    bytenow = bytenow + 1
                end while
            end if

            if width <> 0
                _flags = _flags or 0010b
            end if

            if smb = "."
                _flags = _flags or 0100b
                precision = 0
                load smb byte from ..unformatData:bytenow
                bytenow = bytenow + 1
                if smb = "*"
                    precision = -2
                    load smb byte from ..unformatData:bytenow
                    bytenow = bytenow + 1
                else
                    while smb <= "9" & smb >= "0"
                        precision = precision * 10 + (smb - 0x30)
                        load smb byte from ..unformatData:bytenow
                        bytenow = bytenow + 1
                    end while
                end if
            end if

            if smb = "c"
                type = 0
            else if smb = "d" | smb = "i"
                type = 1
            else if smb = "u"
                type = 2
            else if smb = "x"
                type = 3
            else if smb = "o"
                type = 4
            else if smb = "s"
                type = 5
            else if smb = "S"
                type = 6
            else if smb = "%"
                type = 15
            else
                display "unknown operation type: ", smb, 0Ah
                err
            end if

            db "%"
            if _flags
                db type or _flags shl 4
            else
                smb = type
            end if
            if _flags and 0001b
                if _flags xor 0001b
                    db flags
                else
                    smb = flags
                end if
            end if
            if _flags and 0010b
                if (_flags and 1110b) xor 0010b
                    dd width
                else
                    dw width and 0FFFFh
                    db (width shr 16) and 0FFh 
                    smb = width shr 24
                end if
            end if
            if _flags and 0100b
                if (_flags and 1100b) xor 0100b
                    dd precision
                else
                    dw precision and 0FFFFh
                    db (precision shr 16) and 0FFh 
                    smb = precision shr 24
                end if
            end if
        end if
        db smb
    end while
    common
    db 0
    ..end_format:
}

struc fstr args&{
    local ..bytes, ..start, ..end, lendata
    virtual at 0
        ..bytes::
        ..start:
        fstr args
        ..end:
        lendata = ..end - ..start
    end virtual
    . db lendata dup(?)
    init@cstr ., lendata, ..bytes
    .len = lendata
}
