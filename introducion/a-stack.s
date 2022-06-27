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
    # Just a printf function call
    # %esi saves the first argument
    # to any function call.
    movl .len_stack(%rip), %esi
    leaq .printlen(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movl $0, %eax
    ret

push_value:
    # %r14d register set the value to be pushed.
    addq $4, %rbp
    movl %r14d, (%rbp)
    movl .len_stack(%rip), %eax
    incl %eax
    movl %eax, .len_stack(%rip)
    ret

is_empty:
    # When the stack is empty this function will
    # be called.
    leaq .empty_stack(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movl $0, %eax
    ret

pop_value:
    # If there are elements in the stack
    # the pop operation could be done,
    # call is_empty function otherwise
    # to don't get errors.
    cmpl $0, .len_stack(%rip)
    je is_empty
    movl $0, (%rbp)
    subq $4, %rbp
    movl .len_stack(%rip), %eax
    decl %eax
    movl %eax, .len_stack(%rip)
    ret

print_element:
    # Prints the current element in the stack
    movl (%rbp), %esi
    leaq .printele(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movl $0, %eax
    # decreses to %r15d which is working as
    # an index to know if is not the end
    # of the stack.
    decl %r15d
    # To get the next element into the stack.
    subq $4, %rbp
    call print_loop
    ret
print_loop:
    # %r15d works as index, while %r145d is not
    # zero still there are elements.
    cmpl $0, %r15d
    jg print_element
    ret
print_stack:
    # Getting the value of %rbp and setting it
    # in %r14 since %rbp will be modified
    movq %rbp, %r14
    # Getting the size of the stack.
    movl .len_stack(%rip), %r15d
    call print_loop
    # Setting the initial value of %rbp
    # to don't lost the values
    movq %r14, %rbp
    leaq .endstack(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movl $0, %eax
    ret

main:
    pushq %rbp
    movq %rsp, %rbp

    # 1 #
    movl $1, %r14d
    call push_value

    # 2 #
    # 1 #
    movl $2, %r14d
    call push_value

    # 3 #
    # 2 #
    # 1 #
    movl $3, %r14d
    call push_value

    call print_len_stack
    call print_stack

    # 3 # poped
    call pop_value
    # 2 # poped
    call pop_value
    # 1 # poped
    call pop_value
    # There are not elements #
    call pop_value

    # 16 #
    movl $16, %r14d
    call push_value
    call print_stack

    movq $60, %rax
    movq $0, %rdi
    syscall
    leave
    ret
