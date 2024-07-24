"use strict";(self.webpackChunkhyve_lang=self.webpackChunkhyve_lang||[]).push([[117],{3128:(e,n,r)=>{r.r(n),r.d(n,{assets:()=>o,contentTitle:()=>c,default:()=>u,frontMatter:()=>s,metadata:()=>a,toc:()=>l});var t=r(4848),i=r(8453);const s={sidebar_position:7,description:"Structures in hyve"},c="Structures",a={id:"guide/structs",title:"Structures",description:"Structures in hyve",source:"@site/docs/guide/structs.md",sourceDirName:"guide",slug:"/guide/structs",permalink:"/Hyve/docs/guide/structs",draft:!1,unlisted:!1,editUrl:"https://github.com/broken-bytes/Hyve-docs/docs/guide/structs.md",tags:[],version:"current",sidebarPosition:7,frontMatter:{sidebar_position:7,description:"Structures in hyve"},sidebar:"tutorialSidebar",previous:{title:"Enumerations",permalink:"/Hyve/docs/guide/enums"},next:{title:"Contracts",permalink:"/Hyve/docs/guide/contracts"}},o={},l=[{value:"Initialisation",id:"initialisation",level:2}];function d(e){const n={admonition:"admonition",code:"code",em:"em",h1:"h1",h2:"h2",p:"p",pre:"pre",strong:"strong",...(0,i.R)(),...e.components};return(0,t.jsxs)(t.Fragment,{children:[(0,t.jsx)(n.h1,{id:"structures",children:"Structures"}),"\n",(0,t.jsx)(n.p,{children:"Structure are the building blocks for every applications. They are generic, reusable bits of code that contain data and provide functionality in a scoped and secure way.\r\nUnlike other C-based languages, Structures are defined in a single file, freeing the developer from the burden of having to maintain both an interface and implementation."}),"\n",(0,t.jsxs)(n.admonition,{type:"note",children:[(0,t.jsxs)(n.p,{children:["In hyve there is ",(0,t.jsx)(n.strong,{children:"no"})," concept of ",(0,t.jsx)(n.em,{children:"classes"}),"."]}),(0,t.jsx)(n.p,{children:"Structures represent both classes and structs found in other languages as the distinction of reference or value is made via allocation."})]}),"\n",(0,t.jsx)(n.p,{children:"A struct is defined like this:"}),"\n",(0,t.jsx)(n.pre,{children:(0,t.jsx)(n.code,{className:"language-hyve",children:"struct {\r\n    ...\r\n}\n"})}),"\n",(0,t.jsx)(n.p,{children:"Structures may contain properties (variables) and functions (both reading and mutating):"}),"\n",(0,t.jsx)(n.pre,{children:(0,t.jsx)(n.code,{className:"language-hyve",children:"struct Ticket {\r\n    let price = 22.99\r\n    let seat = 3\r\n    let row = 23\r\n}\r\n\r\nstruct TicketServer {\r\n    var leftTickets: [Ticket] = [Ticket { price: 22.99, seat: 2, row: 23 }]\r\n\r\n    mut fn buyTicket(row: Int, seat: Int) {\r\n        // Find ticket and remove it from the array ...\r\n        self.leftTickets.remove(...)\r\n    }\r\n\r\n    fn availableTickets() -> [Ticket]& {\r\n        return self.leftTickets\r\n    }\r\n}\n"})}),"\n",(0,t.jsxs)(n.admonition,{type:"note",children:[(0,t.jsxs)(n.p,{children:["Functions inside structs are called ",(0,t.jsx)(n.em,{children:"methods"}),"."]}),(0,t.jsxs)(n.p,{children:["They automatically have a hidden ",(0,t.jsx)(n.code,{children:"self"})," parameter than can be used inside of the function. ",(0,t.jsx)(n.code,{children:"self"})," always points to the object itself."]})]}),"\n",(0,t.jsx)(n.h2,{id:"initialisation",children:"Initialisation"}),"\n",(0,t.jsx)(n.p,{children:"Every struct can be initialised in two different ways"}),"\n",(0,t.jsx)(n.p,{children:"If all properties are accessible from outside the struct: Via the object literal:"}),"\n",(0,t.jsx)(n.pre,{children:(0,t.jsx)(n.code,{className:"language-hyve",children:"struct Ticket {\r\n    let price: Float\r\n}\r\n\r\nvar ticket = Ticket { price: 23.99 }\n"})}),"\n",(0,t.jsxs)(n.admonition,{type:"note",children:[(0,t.jsx)(n.p,{children:"The properties of the struct need to have a possible default value if the object literal is used."}),(0,t.jsx)(n.p,{children:"Otherwise the compiler will result in an error when not all properties are assigned in the object literal."}),(0,t.jsx)(n.p,{children:"Invalid example:"}),(0,t.jsx)(n.pre,{children:(0,t.jsx)(n.code,{className:"language-hyve",children:"struct User {\r\n    let userId: Int\r\n}\r\n\r\nstruct Ticket {\r\n    let price: Float\r\n    let user: User\r\n}\r\n\r\n// Error: user has no default value but was not initialised in object literal\r\nvar ticket = Ticket { price: 23.99 }\n"})})]}),"\n",(0,t.jsxs)(n.p,{children:["Or via a special ",(0,t.jsx)(n.code,{children:"init"})," function:"]}),"\n",(0,t.jsx)(n.pre,{children:(0,t.jsx)(n.code,{className:"language-hyve",children:"struct Ticket {\r\n    let price: Float\r\n\r\n    init(price: Float) {\r\n        self.price = price\r\n    }\r\n}\r\n\r\nvar ticket = Ticket(price: 23.99)\n"})}),"\n",(0,t.jsx)(n.p,{children:"When using init, every property must be initialised:"}),"\n",(0,t.jsx)(n.pre,{children:(0,t.jsx)(n.code,{className:"language-hyve",children:"struct Ticket {\r\n    let price: Float\r\n    let seat: Int\r\n\r\n    init(price: Float) {\r\n        self.price = price\r\n        // Error: seat was not initialised in init\r\n    }\r\n}\r\n\r\nvar ticket = Ticket(price: 23.99)\n"})}),"\n",(0,t.jsx)(n.p,{children:"To allow default values for custom structs, an empty init can be provided:"}),"\n",(0,t.jsx)(n.pre,{children:(0,t.jsx)(n.code,{className:"language-hyve",children:"struct User {\r\n    var userId: Int\r\n\r\n    init() {\r\n        userId = 0\r\n    }\r\n}\r\n\r\n// Now we can do this:\r\nstruct Ticket {\r\n    let row: Int\r\n    let price: Float\r\n    let user: User\r\n}\r\n\r\n// User is automatically created via its default `init`\r\nvar ticket = Ticket { row: 1, price: 22.99 }\n"})}),"\n",(0,t.jsxs)(n.p,{children:["A struct may have multiple ",(0,t.jsx)(n.code,{children:"init"})," functions, as long as all properties are assigned. One ",(0,t.jsx)(n.code,{children:"init"})," may call another to achieve this:"]}),"\n",(0,t.jsx)(n.pre,{children:(0,t.jsx)(n.code,{className:"language-hyve",children:"struct User {\r\n    let userId: Int\r\n    var money: Float\r\n\r\n    init(userId: Int, money: Float) {\r\n        self.userId = userId\r\n        self.money = money\r\n    }\r\n\r\n    init() {\r\n        init(userId: 0, money: 0)\r\n    }\r\n\r\n    init(userId: Int) {\r\n        init(userId: userId, money: 0)\r\n    }\r\n\r\n    init(money: Float) {\r\n        init(userId: 0, money: 22.99)\r\n    }\r\n}\n"})}),"\n",(0,t.jsx)(n.admonition,{type:"note",children:(0,t.jsxs)(n.p,{children:["When an ",(0,t.jsx)(n.code,{children:"init"})," function is provided, the compiler disallows using the object literal"]})})]})}function u(e={}){const{wrapper:n}={...(0,i.R)(),...e.components};return n?(0,t.jsx)(n,{...e,children:(0,t.jsx)(d,{...e})}):d(e)}},8453:(e,n,r)=>{r.d(n,{R:()=>c,x:()=>a});var t=r(6540);const i={},s=t.createContext(i);function c(e){const n=t.useContext(s);return t.useMemo((function(){return"function"==typeof e?e(n):{...n,...e}}),[n,e])}function a(e){let n;return n=e.disableParentContext?"function"==typeof e.components?e.components(i):e.components||i:c(e.components),t.createElement(s.Provider,{value:n},e.children)}}}]);