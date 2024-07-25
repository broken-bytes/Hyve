"use strict";(self.webpackChunkhyve_lang=self.webpackChunkhyve_lang||[]).push([[4687],{8917:(n,r,e)=>{e.r(r),e.d(r,{assets:()=>c,contentTitle:()=>a,default:()=>g,frontMatter:()=>s,metadata:()=>o,toc:()=>d});var t=e(4848),i=e(8453);const s={sidebar_position:1,description:"The string type used for convenient text handling."},a="String",o={id:"standard-library/containers/string",title:"String",description:"The string type used for convenient text handling.",source:"@site/docs/standard-library/containers/string.md",sourceDirName:"standard-library/containers",slug:"/standard-library/containers/string",permalink:"/docs/next/standard-library/containers/string",draft:!1,unlisted:!1,editUrl:"https://github.com/broken-bytes/Hyve-docs/docs/standard-library/containers/string.md",tags:[],version:"current",sidebarPosition:1,frontMatter:{sidebar_position:1,description:"The string type used for convenient text handling."},sidebar:"tutorialSidebar",previous:{title:"Containers",permalink:"/docs/next/category/containers"}},c={},d=[{value:"Working with Strings",id:"working-with-strings",level:2},{value:"Substrings",id:"substrings",level:2},{value:"String attributes",id:"string-attributes",level:2},{value:"String ranges",id:"string-ranges",level:2},{value:"String comparison",id:"string-comparison",level:2},{value:"String Views",id:"string-views",level:2}];function l(n){const r={admonition:"admonition",code:"code",h1:"h1",h2:"h2",p:"p",pre:"pre",...(0,i.R)(),...n.components};return(0,t.jsxs)(t.Fragment,{children:[(0,t.jsx)(r.h1,{id:"string",children:"String"}),"\n",(0,t.jsx)(r.p,{children:"The string container type is a wrapper over a char array with automatic memory management, resizing and shrinking. It provides common functionality like substrings, string-ranges and string comparisons."}),"\n",(0,t.jsx)(r.h2,{id:"working-with-strings",children:"Working with Strings"}),"\n",(0,t.jsx)(r.p,{children:"Strings are created like any other struct type:"}),"\n",(0,t.jsx)(r.pre,{children:(0,t.jsx)(r.code,{className:"language-hyve",children:'// Define the type and convert char array to String implicitly\nvar string: String = ""\n// Or create a string explicitly\nvar string = String.create("")\n'})}),"\n",(0,t.jsx)(r.admonition,{type:"note",children:(0,t.jsxs)(r.p,{children:["String fulfills the ",(0,t.jsx)(r.code,{children:"Convertible"})," and ",(0,t.jsx)(r.code,{children:"Constructable"})," contracts so it can be used as a char pointer, or created via a char array."]})}),"\n",(0,t.jsx)(r.h2,{id:"substrings",children:"Substrings"}),"\n",(0,t.jsx)(r.p,{children:"Strings may be sliced into substrings. Substrings are parts of a string."}),"\n",(0,t.jsx)(r.p,{children:"Creating a substring is easy:"}),"\n",(0,t.jsx)(r.pre,{children:(0,t.jsx)(r.code,{className:"language-hyve",children:'var str: String = "Foo, Bar"\n\n// Reads `Foo`\nvar foo = str.substring(from: 0, count: 3)\n'})}),"\n",(0,t.jsxs)(r.p,{children:["Alternatively, a substring can be constructed from ",(0,t.jsx)(r.code,{children:"from"})," to ",(0,t.jsx)(r.code,{children:"to"}),":"]}),"\n",(0,t.jsx)(r.pre,{children:(0,t.jsx)(r.code,{className:"language-hyve",children:'var str: String = "Foo, Bar"\n\n// Reads `Foo`\nvar foo = str.substring(from: 0, to: 2)\n'})}),"\n",(0,t.jsx)(r.admonition,{type:"danger",children:(0,t.jsx)(r.p,{children:"Both substring functions will result in a panic if the string does not have enough characters"})}),"\n",(0,t.jsx)(r.h2,{id:"string-attributes",children:"String attributes"}),"\n",(0,t.jsxs)(r.p,{children:["The length of a string is retrieved by accessing the ",(0,t.jsx)(r.code,{children:"length"})," property:"]}),"\n",(0,t.jsx)(r.pre,{children:(0,t.jsx)(r.code,{className:"language-hyve",children:'var str: String = "Foo, Bar"\n\n// Prints 8\nprint(str.length)\n'})}),"\n",(0,t.jsxs)(r.p,{children:["The underlying memory can be accessed via the ",(0,t.jsx)(r.code,{children:"data()"})," function:"]}),"\n",(0,t.jsx)(r.pre,{children:(0,t.jsx)(r.code,{className:"language-hyve",children:'var str: String = "Foo, Bar"\n\n// Prints some address\nprint(str.data())\n'})}),"\n",(0,t.jsx)(r.h2,{id:"string-ranges",children:"String ranges"}),"\n",(0,t.jsxs)(r.p,{children:["String fulfills the ",(0,t.jsx)(r.code,{children:"Iterable"})," contract, allowing it to be used by iterators like ",(0,t.jsx)(r.code,{children:"for"})," loops:"]}),"\n",(0,t.jsx)(r.pre,{children:(0,t.jsx)(r.code,{className:"language-hyve",children:'var str: String = "Foo, Bar, Foobar"\n\n// Use each character\nfor character in str {\n    ...\n}\n'})}),"\n",(0,t.jsx)(r.h2,{id:"string-comparison",children:"String comparison"}),"\n",(0,t.jsxs)(r.p,{children:["String fulfills the ",(0,t.jsx)(r.code,{children:"Comparable"})," contract, allowing it to be compared against char arrays and other strings or string views:"]}),"\n",(0,t.jsx)(r.pre,{children:(0,t.jsx)(r.code,{className:"language-hyve",children:'var foo = "Foo"\nvar fooStr: String = "Foo"\n\n// Compare\nif foo == fooStr {\n    // Works because String has a `compare(with: Char*)` function.\n}\n'})}),"\n",(0,t.jsx)(r.h2,{id:"string-views",children:"String Views"}),"\n",(0,t.jsx)(r.p,{children:"A string view is a non-owning reference to a string. It only holds an immutable reference, allowing comparison and iteration of the string. Views are faster to pass around and are geenrally favoured when ownership should remain on the string the veiw was created for."}),"\n",(0,t.jsx)(r.p,{children:"A string view is created like this:"}),"\n",(0,t.jsx)(r.pre,{children:(0,t.jsx)(r.code,{className:"language-hyve",children:'var str: String = "Foo, Bar"\nvar view = StringView.from(string: str)\n\n// Iterate over the characters like it was a regular string\nfor character in view {\n    ...\n}\n'})})]})}function g(n={}){const{wrapper:r}={...(0,i.R)(),...n.components};return r?(0,t.jsx)(r,{...n,children:(0,t.jsx)(l,{...n})}):l(n)}},8453:(n,r,e)=>{e.d(r,{R:()=>a,x:()=>o});var t=e(6540);const i={},s=t.createContext(i);function a(n){const r=t.useContext(s);return t.useMemo((function(){return"function"==typeof n?n(r):{...r,...n}}),[r,n])}function o(n){let r;return r=n.disableParentContext?"function"==typeof n.components?n.components(i):n.components||i:a(n.components),t.createElement(s.Provider,{value:r},n.children)}}}]);