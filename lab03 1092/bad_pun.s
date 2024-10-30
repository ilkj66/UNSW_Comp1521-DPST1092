main:
        la $a0, badp
        li $v0, 4
        syscall
        jr $ra
.data
badp:
        .asciiz "Well, this was a MIPStake!\n"