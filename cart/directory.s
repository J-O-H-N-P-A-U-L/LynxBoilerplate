;
; Karri Kaksonen, 2011
;
; A default directory with just the main executable.
;
	.include "lynx.inc"
	.import         __STARTOFDIRECTORY__
	.import         __RAM_START__
	.import         __CODE_SIZE__,__DATA_SIZE__,__RODATA_SIZE__
	.import		__STARTUP_SIZE__,__INIT_SIZE__
	.import		__BLOCKSIZE__
	.import         __game_CODE_LOAD__
	.import         __game_CODE_SIZE__,__game_DATA_SIZE__
	.import         __POPCORN_RODATA_LOAD__
	.import         __POPCORN_RODATA_SIZE__
	.import         __INTRO_CODE_LOAD__
	.import         __INTRO_CODE_SIZE__,__INTRO_DATA_SIZE__,__INTRO_RODATA_SIZE__


; ------------------------------------------------------------------------
; Lynx directory
	.segment "DIRECTORY"

__DIRECTORY_START__:
off0=__STARTOFDIRECTORY__+(__DIRECTORY_END__-__DIRECTORY_START__)

; Entry 0 - first executable
block0=off0/__BLOCKSIZE__
len0=__STARTUP_SIZE__+__INIT_SIZE__+__CODE_SIZE__+__DATA_SIZE__+__RODATA_SIZE__
        .byte   <block0
        .word   off0 & (__BLOCKSIZE__ - 1)
        .byte   $88
        .word   __RAM_START__
        .word   len0
off1=off0+len0

; Entry 1 - game
block1=off1/__BLOCKSIZE__
len1=__game_CODE_SIZE__+__game_DATA_SIZE__
        .byte   <block1
        .word   off1 & (__BLOCKSIZE__ - 1)
        .byte   $88
        .word   __game_CODE_LOAD__
        .word   len1
off2=off1+len1

; Entry 2 - popcorn
block2=off2/__BLOCKSIZE__
len2=__POPCORN_RODATA_SIZE__
        .byte   <block2
        .word   off2 & (__BLOCKSIZE__ - 1)
        .byte   $88
        .word   __POPCORN_RODATA_LOAD__
        .word   len2
off3=off2+len2

block3=off3/__BLOCKSIZE__
len3=__INTRO_CODE_SIZE__+__INTRO_RODATA_SIZE__
        .byte   <block3
        .word   off3 & (__BLOCKSIZE__ - 1)
        .byte   $88
        .word   __INTRO_CODE_LOAD__
        .word   len3
off4=off3+len3

__DIRECTORY_END__:

