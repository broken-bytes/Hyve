"use strict";(self.webpackChunkhyve_lang=self.webpackChunkhyve_lang||[]).push([[6252],{9581:(e,n,a)=>{a.r(n),a.d(n,{assets:()=>o,contentTitle:()=>s,default:()=>c,frontMatter:()=>l,metadata:()=>r,toc:()=>d});var t=a(4848),i=a(8453);const l={sidebar_position:1,description:"The three different storage types in Hyve"},s="Variables, Mutables, Immutables",r={id:"guide/variables-mutables-immutables",title:"Variables, Mutables, Immutables",description:"The three different storage types in Hyve",source:"@site/docs/guide/variables-mutables-immutables.md",sourceDirName:"guide",slug:"/guide/variables-mutables-immutables",permalink:"/docs/next/guide/variables-mutables-immutables",draft:!1,unlisted:!1,editUrl:"https://github.com/broken-bytes/Hyve-docs/docs/guide/variables-mutables-immutables.md",tags:[],version:"current",sidebarPosition:1,frontMatter:{sidebar_position:1,description:"The three different storage types in Hyve"},sidebar:"tutorialSidebar",previous:{title:"Guide",permalink:"/docs/next/category/guide"},next:{title:"Builtin Types",permalink:"/docs/next/guide/builtins"}},o={},d=[{value:"The right level of immutability",id:"the-right-level-of-immutability",level:2},{value:"Variables",id:"variables",level:3},{value:"Mutables",id:"mutables",level:3},{value:"Immutables",id:"immutables",level:3},{value:"Why a third level?",id:"why-a-third-level",level:2},{value:"Declaring variables",id:"declaring-variables",level:2},{value:"Type-inference",id:"type-inference",level:2},{value:"Optionals",id:"optionals",level:2},{value:"Optional unwrapping",id:"optional-unwrapping",level:3},{value:"Pointers and References",id:"pointers-and-references",level:2}];function h(e){const n={admonition:"admonition",code:"code",em:"em",h1:"h1",h2:"h2",h3:"h3",li:"li",p:"p",pre:"pre",strong:"strong",ul:"ul",...(0,i.R)(),...e.components};return(0,t.jsxs)(t.Fragment,{children:[(0,t.jsx)(n.h1,{id:"variables-mutables-immutables",children:"Variables, Mutables, Immutables"}),"\n",(0,t.jsxs)(n.p,{children:["Hyve provides ",(0,t.jsx)(n.em,{children:"variables"})," that allow developers to store values in a named storage. There are three different types of ",(0,t.jsx)(n.em,{children:"variables"})," in Hyve.\nVariables (fully mutable), Mutables (partially mutable), and Immutables (immutable)."]}),"\n",(0,t.jsx)(n.p,{children:"Every variable has a fixed type that cannot be changed after declaration in Hyve.\nThis way, the best possible type-safety is ensured, leaving no room for type or implicit conversion errors."}),"\n",(0,t.jsx)(n.h2,{id:"the-right-level-of-immutability",children:"The right level of immutability"}),"\n",(0,t.jsx)(n.p,{children:"Hyve has a different approach on variables as seen in other languages. Instead of providing mutable and immutable(not really) storage types, it offers three different levels of immutability."}),"\n",(0,t.jsx)(n.p,{children:"This way, the meaning and behaviour of each piece of code is clearly readable without having to scim through all the surrounding blocks of code."}),"\n",(0,t.jsx)(n.h3,{id:"variables",children:"Variables"}),"\n",(0,t.jsxs)(n.p,{children:["Variables in Hyve are defined via ",(0,t.jsx)(n.code,{children:"var"}),". They behave like variables in every language. Both the reference and the value can be changed. For pointers this means the pointer can be changed, and the memory it points to."]}),"\n",(0,t.jsx)(n.h3,{id:"mutables",children:"Mutables"}),"\n",(0,t.jsxs)(n.p,{children:["Mutables are defined via ",(0,t.jsx)(n.code,{children:"val"}),". Mutables are one level less mutable than variables. Instead of allowing change to the reference or pointer, they only allow changes to the underlying value or memory.\nThis is the same behaviour like found in languages like Kotlin (",(0,t.jsx)(n.code,{children:"val"}),") or Swift (",(0,t.jsx)(n.code,{children:"let"}),")."]}),"\n",(0,t.jsx)(n.h3,{id:"immutables",children:"Immutables"}),"\n",(0,t.jsxs)(n.p,{children:["Immutables are defined via ",(0,t.jsx)(n.code,{children:"let"}),". Unlike in most other modern languages, Hyve offers a third level of immutability. Immutables neither allow changes to the object, nor to the reference. They are truly immutable references."]}),"\n",(0,t.jsx)(n.h2,{id:"why-a-third-level",children:"Why a third level?"}),"\n",(0,t.jsx)(n.p,{children:"Many languages mitigate the issue of truly immutable objects by using a constant object that itself only has constant properties. While this is a suitable way of doing it, it comes with drawbacks:"}),"\n",(0,t.jsxs)(n.ul,{children:["\n",(0,t.jsx)(n.li,{children:"The object is immutable for every part of the code except where its constructor is called."}),"\n",(0,t.jsx)(n.li,{children:"It's impossible to change the object's properties at one part of the code and let other parts listen to it."}),"\n",(0,t.jsx)(n.li,{children:"True immutability is subject to conventions within the codebase - thus objects can become mutable any time if a developer adds at least one mutable property."}),"\n"]}),"\n",(0,t.jsx)(n.p,{children:"These drawbacks lead to the decision to incorparate a third level of immutability."}),"\n",(0,t.jsx)(n.admonition,{type:"note",children:(0,t.jsxs)(n.p,{children:["Immutables are only immutable on the ",(0,t.jsx)(n.code,{children:"let"})," reference. There can be other, mutable references to the same object.\nImmutables only guarantee that the object cannot get mutated from that very reference."]})}),"\n",(0,t.jsx)(n.h2,{id:"declaring-variables",children:"Declaring variables"}),"\n",(0,t.jsx)(n.p,{children:"The three different storage types are declared like this:"}),"\n",(0,t.jsx)(n.pre,{children:(0,t.jsx)(n.code,{className:"language-hyve",children:"// A variable\nvar data: Int = 3\n// A mutable\nval data: Int = 3\n// An immutable\nlet data: Int = 3\n"})}),"\n",(0,t.jsxs)(n.p,{children:["If there are multiple branches like a ",(0,t.jsx)(n.code,{children:"when"})," or ",(0,t.jsx)(n.code,{children:"if/else"}),", the variable may be declared at top but only defined in each branch:"]}),"\n",(0,t.jsx)(n.pre,{children:(0,t.jsx)(n.code,{className:"language-hyve",children:"var data: Int\n\nif someValue {\n    data = 3\n} else {\n    data = 2\n}\n"})}),"\n",(0,t.jsx)(n.admonition,{type:"note",children:(0,t.jsxs)(n.p,{children:["Hyve does ",(0,t.jsx)(n.strong,{children:"not"})," not allow defining multiple variables in a single line like this: var x = 0, y = 1, z = 2."]})}),"\n",(0,t.jsx)(n.h2,{id:"type-inference",children:"Type-inference"}),"\n",(0,t.jsxs)(n.p,{children:["Hyve also comes with a powerful feature called ",(0,t.jsx)(n.em,{children:"type-inference"}),".\nType-inference allows developers to omit the type from the variable declaration as long as the variable declaration includes an assignment. This assignment is evaluated at compile time to get the correct type."]}),"\n",(0,t.jsx)(n.p,{children:"If the variable shall not have an assignment immediately, the type must be defined. Every variable needs a value, otherwise the compiler will issue an error. This is to enforce memory safety by default, disallowing empty variables or unassigned memory."}),"\n",(0,t.jsx)(n.p,{children:"This is what type inference looks like:"}),"\n",(0,t.jsx)(n.pre,{children:(0,t.jsx)(n.code,{className:"language-hyve",children:"// Inferred to be Int because `3` is an integer literal\nvar data = 3\n"})}),"\n",(0,t.jsx)(n.h2,{id:"optionals",children:"Optionals"}),"\n",(0,t.jsxs)(n.p,{children:["If variables should be allowed to be empty or uninitialised, they can be declared ",(0,t.jsx)(n.em,{children:"optional"}),".\nOptionals are wrappers over regular variables, just that they allow them to ",(0,t.jsx)(n.strong,{children:"not"})," have a value. Optionals are defined by appending ",(0,t.jsx)(n.code,{children:"?"})," to the type."]}),"\n",(0,t.jsx)(n.admonition,{type:"note",children:(0,t.jsxs)(n.p,{children:["Only variables (",(0,t.jsx)(n.code,{children:"var"}),") can be declared optionals. This is to ensure that the reference may be changed, so that the variable does hold a value at a later stage."]})}),"\n",(0,t.jsxs)(n.p,{children:["When an optional has ",(0,t.jsx)(n.em,{children:"no"})," value, it holds a special value called ",(0,t.jsx)(n.code,{children:"none"}),"."]}),"\n",(0,t.jsx)(n.p,{children:"This is how to declare optionals:"}),"\n",(0,t.jsx)(n.pre,{children:(0,t.jsx)(n.code,{className:"language-hyve",children:"var data: Int? = .none\ndata = 3\n"})}),"\n",(0,t.jsx)(n.h3,{id:"optional-unwrapping",children:"Optional unwrapping"}),"\n",(0,t.jsxs)(n.p,{children:["Optionals need unwrapping before their values can be used. Unwrapping an optional is done by either using ",(0,t.jsx)(n.code,{children:"?"})," (safe unwrapping) or ",(0,t.jsx)(n.code,{children:"!"})," (force unwrapping).\nSafe unwrapping only executes the code when the optional is not ",(0,t.jsx)(n.code,{children:"none"}),", resuling in safer code. ",(0,t.jsx)(n.code,{children:"!"})," should only be used when it is certain that the optional holds a value. ",(0,t.jsx)(n.code,{children:"!"})," skips runtime checks ensuring increased performance but comes at the cost of possible memory read errors, leading to crashes that aren't catchable."]}),"\n",(0,t.jsx)(n.p,{children:"This is what unwrapping looks like:"}),"\n",(0,t.jsx)(n.pre,{children:(0,t.jsx)(n.code,{className:"language-hyve",children:"// Empty value variable\nvar value: Int? = .none\n// Assign to a new variable (value2), use a default value if value is `none`\nvar value2 = value? ?? 2\n// Skip safety checks, unwrap the optional and assign it to the other variable\n// In this setup, this would crash as value is `none`\nvar value3 = value!\n"})}),"\n",(0,t.jsxs)(n.admonition,{type:"danger",children:[(0,t.jsxs)(n.p,{children:["Force-unwrapping should only be done when it can be made 100% sure that the optional is not ",(0,t.jsx)(n.code,{children:"none"}),". Force-unwrapping an empty optional crashes the application as it results in a ",(0,t.jsx)(n.code,{children:"panic"}),"."]}),(0,t.jsxs)(n.p,{children:["There is ",(0,t.jsx)(n.strong,{children:"no"})," way to prevent such crashes."]})]}),"\n",(0,t.jsx)(n.h2,{id:"pointers-and-references",children:"Pointers and References"}),"\n",(0,t.jsx)(n.p,{children:"Hyve allows direct access to memory, utilising both the heap and the stack. By default, every allocation is done on the stack, but Hyve provides ways to allocate on the heap."}),"\n",(0,t.jsx)(n.p,{children:"Due to that, Hyve introduces pointer and reference types."}),"\n",(0,t.jsx)(n.p,{children:"A pointer type is defined like this:"}),"\n",(0,t.jsx)(n.pre,{children:(0,t.jsx)(n.code,{className:"language-hyve",children:"var value = 23\n// Allocate a single integer on the heap\nvar data: Int* = allocator.alloc(Int, 1)\n// Assigns the value of `value` to `data`. Does not change the pointer but only the object it points to.\ndata = value\n"})}),"\n",(0,t.jsx)(n.admonition,{type:"tip",children:(0,t.jsxs)(n.p,{children:["Allocations are done via ",(0,t.jsx)(n.em,{children:"allocators"})," in Hyve. The standard library provides default allocators."]})}),"\n",(0,t.jsx)(n.p,{children:"When we want to use the address of another variable we can use the reference syntax:"}),"\n",(0,t.jsx)(n.pre,{children:(0,t.jsx)(n.code,{className:"language-hyve",children:"var value = 23\n// Assigns the address of `value` to `data`. Does change the pointer\nvar data: Int* = &value\n"})}),"\n",(0,t.jsxs)(n.p,{children:["Since the compiler can infer that we want a pointer to ",(0,t.jsx)(n.code,{children:"Int"})," we can omit the type definition:"]}),"\n",(0,t.jsx)(n.pre,{children:(0,t.jsx)(n.code,{className:"language-hyve",children:"var value = 23\n// Assigns the address of `value` to `data`. Does change the pointer\nvar data = &value\n"})}),"\n",(0,t.jsx)(n.p,{children:"Pointers can also be optionals like this:"}),"\n",(0,t.jsx)(n.pre,{children:(0,t.jsx)(n.code,{className:"language-hyve",children:"var ptr: Int*? = .none\n"})}),"\n",(0,t.jsx)(n.admonition,{type:"note",children:(0,t.jsx)(n.p,{children:"Hyve does not allow pointers to be uninitialised. A pointer always needs to have an underlying value, unless defined as optional."})})]})}function c(e={}){const{wrapper:n}={...(0,i.R)(),...e.components};return n?(0,t.jsx)(n,{...e,children:(0,t.jsx)(h,{...e})}):h(e)}},8453:(e,n,a)=>{a.d(n,{R:()=>s,x:()=>r});var t=a(6540);const i={},l=t.createContext(i);function s(e){const n=t.useContext(l);return t.useMemo((function(){return"function"==typeof e?e(n):{...n,...e}}),[n,e])}function r(e){let n;return n=e.disableParentContext?"function"==typeof e.components?e.components(i):e.components||i:s(e.components),t.createElement(l.Provider,{value:n},e.children)}}}]);