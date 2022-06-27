.text
.section .rodata
    .globl main
    .type main, @function

    .data
    .len_stack:
        .long 0
    .printlen:
        .string "LEN: %d\n\n"
        .text
    .printele:
        .string "ELEMENT: %d\n"
        .text
    .endstack:
        .string "-- END STACK --\n\n"
        .text
    .empty_stack:
        .string "-- EMPTY STACK --\n\n"
        .text

print_len_stack:
    movl .len_stack(%rip), %esi
    leaq .printlen(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movl $0, %eax
    ret

push_value:
    # Every value to be pushed must be set
    # on %r14d register
    addq $4, %rbp
    movl %r14d, (%rbp)
    movl .len_stack(%rip), %eax
    incl %eax
    movl %eax, .len_stack(%rip)
    ret

is_empty:
    leaq .empty_stack(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movl $0, %eax
    ret

pop_value:
    cmpl $0, .len_stack(%rip)
    je is_empty
    movl $0, (%rbp)
    subq $4, %rbp
    movl .len_stack(%rip), %eax
    decl %eax
    movl %eax, .len_stack(%rip)
    ret

print_element:
    movl (%rbp), %esi
    leaq .printele(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movl $0, %eax
    decl %r15d
    subq $4, %rbp
    call print_loop
    ret
print_loop:
    cmpl $0, %r15d
    jg print_element
    ret
print_stack:
    movq %rbp, %r14
    movl .len_stack(%rip), %r15d
    call print_loop
    movq %r14, %rbp
    leaq .endstack(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movl $0, %eax
    ret

main:
    pushq %rbp
    movq %rsp, %rbp

    movl $1, %r14d
    call push_value

    movl $2, %r14d
    call push_value

    movl $3, %r14d
    call push_value

    call print_len_stack
    call print_stack


    call pop_value
    call pop_value
    call pop_value
    call pop_value

    movl $16, %r14d
    call push_value
    call print_stack

    movq $60, %rax
    movq $0, %rdi
    syscall
    leave
    ret
