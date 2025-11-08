.text
main:
    addi x5, x0, 5
    addi x6, x0, 10
    jal x1, func
    ecall

func:
    add x7, x5, x6
    addi x10, x0, 10
    ecall
    jalr x0,0(x1)
exit:

