CFG (Contex-Free Grammar) are used for parsing in programming languages and they are almost enough to describe all grammatical rules for some languages.
  - There are essentially two different approach to parsing
      - Bottom-up
      - Top-down<br>


The key concept in parsing is construction syntax tree or abstract syntax tree(AST) with the help of push_down automata.
In bottom-up approach there could be two different fashion but essentially the same
  - first one is using system stack widely known as recursive-descent-parsing
  - second one is mannualy implement stack data structure

In bottom-up approach it is must to not have left-recursive rule in the grammar, for example A -> Aa in which case stack-overflow
occur, so one should do some transformation over the given grammar.
In first two examples we implemented parser for aritmetic expressions with two operation that can be expanded with the rest operations
2, 2+4, 3 + 3*4, 2 + (2+3*(2*2*3(2+3)) + 100) * 21 + 2

Naive grammar (with left-recursive rule)<br>
  E ->  E+T<br> 
        | T<br>
  T ->  T*F<br>
      | F<br>
  F ->  (E)<br>
      | num_token<br>

Transformed grammar <br>
  E ->  TE'	  {num_token, (}<br>
  E'->  +TE'	  {+}<br>
      | eps	  {), eoi}<br>
  T ->  FT'	  {num_token, (}<br>
  T'->  *FT'	  {*}<br>
      | eps	  {), eoi, +}<br>
  F ->  (E)	  {(}<br>
      | num_token	  {num_token}<br>
    
