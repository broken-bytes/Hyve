"use strict";(self.webpackChunkhyve_lang=self.webpackChunkhyve_lang||[]).push([[215],{1272:(e,n,s)=>{s.r(n),s.d(n,{assets:()=>a,contentTitle:()=>r,default:()=>h,frontMatter:()=>l,metadata:()=>t,toc:()=>d});var o=s(4848),i=s(8453);const l={sidebar_position:4,description:"Control flow in Hyve"},r="Control flow",t={id:"guide/control-flow",title:"Control flow",description:"Control flow in Hyve",source:"@site/docs/guide/control-flow.md",sourceDirName:"guide",slug:"/guide/control-flow",permalink:"/docs/guide/control-flow",draft:!1,unlisted:!1,editUrl:"https://github.com/broken-bytes/Hyve-docs/docs/guide/control-flow.md",tags:[],version:"current",sidebarPosition:4,frontMatter:{sidebar_position:4,description:"Control flow in Hyve"},sidebar:"tutorialSidebar",previous:{title:"Comments",permalink:"/docs/guide/comments"},next:{title:"Functions",permalink:"/docs/guide/functions"}},a={},d=[{value:"Conditional Statements",id:"conditional-statements",level:2},{value:"If else",id:"if-else",level:3},{value:"When",id:"when",level:3},{value:"Loops",id:"loops",level:2},{value:"For loops",id:"for-loops",level:3},{value:"While loops",id:"while-loops",level:3}];function c(e){const n={admonition:"admonition",code:"code",h1:"h1",h2:"h2",h3:"h3",p:"p",pre:"pre",strong:"strong",...(0,i.R)(),...e.components};return(0,o.jsxs)(o.Fragment,{children:[(0,o.jsx)(n.h1,{id:"control-flow",children:"Control flow"}),"\n",(0,o.jsxs)(n.p,{children:["Hyve provides a number of control flow structures that make it easy to write understandable and concise code.\nFrom ",(0,o.jsx)(n.code,{children:"if else"})," over ",(0,o.jsx)(n.code,{children:"when"})," to ",(0,o.jsx)(n.code,{children:"guard"})," statements and ultimately ",(0,o.jsx)(n.code,{children:"for"})," and ",(0,o.jsx)(n.code,{children:"while"})," loops."]}),"\n",(0,o.jsx)(n.h2,{id:"conditional-statements",children:"Conditional Statements"}),"\n",(0,o.jsx)(n.h3,{id:"if-else",children:"If else"}),"\n",(0,o.jsx)(n.p,{children:"Hyve allows the traditional if/else if/else branches like most other c-based languages:"}),"\n",(0,o.jsx)(n.pre,{children:(0,o.jsx)(n.code,{className:"language-hyve",children:"if value == 1 {\n    ...\n} else if value == 2 {\n    ...\n} else {\n    ...\n}\n"})}),"\n",(0,o.jsx)(n.p,{children:"Unlike some other languages, they can be expressions and not just statements as well:"}),"\n",(0,o.jsx)(n.pre,{children:(0,o.jsx)(n.code,{className:"language-hyve",children:"var data = if value == 1 {\n    1\n} else if value == 2 {\n    2\n} else {\n    3\n}\n"})}),"\n",(0,o.jsxs)(n.admonition,{type:"warning",children:[(0,o.jsx)(n.p,{children:"If else can only be used as an expression if every branch only has a single expression."}),(0,o.jsx)(n.p,{children:"This doesn't work:"}),(0,o.jsx)(n.pre,{children:(0,o.jsx)(n.code,{className:"language-hyve",children:"var data = if value == 1 {\n    var user = 3\n    user\n} else if value == 2 {\n    2\n} else {\n    3\n}\n"})})]}),"\n",(0,o.jsx)(n.h3,{id:"when",children:"When"}),"\n",(0,o.jsxs)(n.p,{children:["Hyve comes with a keyword different to most other languages. When behaves like ",(0,o.jsx)(n.code,{children:"switch"})," but comes with a few extras.\nInstead of having multiple ",(0,o.jsx)(n.code,{children:"case"}),", and sometimes a ",(0,o.jsx)(n.code,{children:"default"}),", cases, it provides are more intuitive approach. Cases can be ranges or values, not just values:"]}),"\n",(0,o.jsx)(n.pre,{children:(0,o.jsx)(n.code,{className:"language-hyve",children:"when value {\n    0...3 -> ...\n    4 -> ...\n} else {\n    ...\n}\n"})}),"\n",(0,o.jsx)(n.p,{children:"Note how the first case is a range from 0-3 and the second case is just 4."}),"\n",(0,o.jsxs)(n.p,{children:["Additionally, Instead of a ",(0,o.jsx)(n.code,{children:"default"})," case, Hyve introduces the ",(0,o.jsx)(n.code,{children:"else"})," branch for ",(0,o.jsx)(n.code,{children:"when"}),", making code more intuitive to read and write."]}),"\n",(0,o.jsxs)(n.p,{children:[(0,o.jsx)(n.code,{children:"When"})," also works with conditions:"]}),"\n",(0,o.jsx)(n.pre,{children:(0,o.jsx)(n.code,{className:"language-hyve",children:'var str = String("Foo")\n\nwhen str {\n    str == "Foo" -> ...\n    str != "Foo" -> ...\n}\n'})}),"\n",(0,o.jsxs)(n.admonition,{type:"note",children:[(0,o.jsxs)(n.p,{children:["There is no implicit fallthrough in Hyve for ",(0,o.jsx)(n.code,{children:"when"}),". If multiple cases are supposed to do the same, they can be written like this:"]}),(0,o.jsx)(n.pre,{children:(0,o.jsx)(n.code,{className:"language-hyve",children:'when str {\n    "Foo", "foo" -> ...\n} else {\n    ...\n}\n'})}),(0,o.jsxs)(n.p,{children:["Alternatively the ",(0,o.jsx)(n.code,{children:"next"})," keyword indicates that the current case should be ended and the next one shall be executed:"]}),(0,o.jsx)(n.pre,{children:(0,o.jsx)(n.code,{className:"language-hyve",children:'when str {\n    "Foo" -> next\n    "foo" -> ...\n} else {\n    ...\n}\n'})})]}),"\n",(0,o.jsx)(n.h2,{id:"loops",children:"Loops"}),"\n",(0,o.jsx)(n.h3,{id:"for-loops",children:"For loops"}),"\n",(0,o.jsxs)(n.p,{children:["Unlike other languages, Hyve only has a single ",(0,o.jsx)(n.code,{children:"for"})," loop. There is no separate for, for-in, and for-each loop. ",(0,o.jsx)(n.code,{children:"for"})," is used for all of these scenarios."]}),"\n",(0,o.jsx)(n.p,{children:"Iterating over a range:"}),"\n",(0,o.jsx)(n.pre,{children:(0,o.jsx)(n.code,{className:"language-hyve",children:"for x in 0...3 {\n    ...\n}\n"})}),"\n",(0,o.jsxs)(n.p,{children:["if the index in range-based loop is not needed, it can be discarded by using ",(0,o.jsx)(n.code,{children:"_"}),":"]}),"\n",(0,o.jsx)(n.pre,{children:(0,o.jsx)(n.code,{className:"language-hyve",children:"for _ in 0...3 {\n    ...\n}\n"})}),"\n",(0,o.jsx)(n.p,{children:"Iterating over the elements of an array:"}),"\n",(0,o.jsx)(n.pre,{children:(0,o.jsx)(n.code,{className:"language-hyve",children:"var items: [Int] = [1, 2, 3]\n\nfor item in items {\n    ...\n}\n"})}),"\n",(0,o.jsx)(n.h3,{id:"while-loops",children:"While loops"}),"\n",(0,o.jsx)(n.p,{children:"While loops repeat their body until the condition of the loop's head is no longer fulfilled:"}),"\n",(0,o.jsx)(n.pre,{children:(0,o.jsx)(n.code,{className:"language-hyve",children:"var isLoggedIn = true\n\nwhile isLoggedIn {\n    ...\n}\n"})}),"\n",(0,o.jsxs)(n.p,{children:["While loops also come with their cousin, ",(0,o.jsx)(n.code,{children:"do-while"}),". Do-while behaves exactly the same, just that the condition is evaluated ",(0,o.jsx)(n.strong,{children:"after"})," each run, which means a ",(0,o.jsx)(n.code,{children:"do-while"})," loop ",(0,o.jsx)(n.strong,{children:"always"})," runs at least once:"]}),"\n",(0,o.jsx)(n.pre,{children:(0,o.jsx)(n.code,{className:"language-hyve",children:"var isLoggedIn = true\n\ndo {\n    ...\n} while isLoggedIn\n"})}),"\n",(0,o.jsxs)(n.admonition,{type:"tip",children:[(0,o.jsxs)(n.p,{children:["You can end the current iteration of every loop with the keyword ",(0,o.jsx)(n.code,{children:"continue"}),":"]}),(0,o.jsx)(n.pre,{children:(0,o.jsx)(n.code,{className:"language-hyve",children:"while foo {\n    if bar {\n        continue\n    }\n}\n"})})]})]})}function h(e={}){const{wrapper:n}={...(0,i.R)(),...e.components};return n?(0,o.jsx)(n,{...e,children:(0,o.jsx)(c,{...e})}):c(e)}},8453:(e,n,s)=>{s.d(n,{R:()=>r,x:()=>t});var o=s(6540);const i={},l=o.createContext(i);function r(e){const n=o.useContext(l);return o.useMemo((function(){return"function"==typeof e?e(n):{...n,...e}}),[n,e])}function t(e){let n;return n=e.disableParentContext?"function"==typeof e.components?e.components(i):e.components||i:r(e.components),o.createElement(l.Provider,{value:n},e.children)}}}]);