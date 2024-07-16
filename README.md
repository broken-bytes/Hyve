<p align="center">
  <img src="https://i.imgur.com/f7XHEDZ.png" style="height:250px;" />
</p>

# Hyve Programming Language
![Static Badge](https://img.shields.io/badge/C%2B%2B-20-purple) ![GitHub Release](https://img.shields.io/github/v/release/broken-bytes/Hyve?include_prereleases&sort=semver&label=version)
![GitHub branch check runs](https://img.shields.io/github/check-runs/broken-bytes/Hyve/main) 

## Overview
Hyve is a modern, highly asynchronous programming language designed for building scalable and efficient software. Embracing the latest in concurrent programming paradigms, Hyve offers a unique blend of performance, simplicity, and flexibility for developers.

## Features
- 🔮 **Full control**: No nasty Garbage Collector, no heavy runtime. Just manual memory management made beautiful.
- 🧊 **Immutability**: Immutable data structures and functions by default to increase robustness and predictability. 
- 🧵 **Asynchronous by Nature**: At its core, Hyve is built to handle asynchronous operations seamlessly.
- 🔮 **Modern Syntax**: Clean and expressive syntax, enabling developers to achieve more with fewer lines and clear readability.
- 🎚️ **Scalability**: Stay small or go big. Hyve handles large-scale applications easily - from microservices to massive cloud-based systems.
- 🔗 **Strong Typing with Inference**: Strong typing capabilities with intelligent type inference.
- 🤝 **Cross-Platform Compatibility**: Write once, run anywhere. Hyve code is highly portable across various platforms.
- 🔋 **Batteries included**: Sophisticated standard library and first-class frameworks for various of tasks.
- 🔒 **Secure by design**: Highest standards on security, ensuring your apps are safe by default.

## Installation
```bash
# Replace <version> with the desired version
curl -sSL https://hyve-lang.org/install.sh | sh -s -- <version>
```

## Quick Start
A simple "Hello, World!" in Hyve:

```hyve
struct World {
  let name: String

  init(name: String) {
    self.name = name
  }

  fn hello() -> String {
    "Hello World"
  }
}

fn main() {
    let world = World()
    print(world.hello())
}
```

## Documentation
Visit [Hyve Documentation](https://hyve-lang.org/docs) for detailed guides, API references, and tutorials.

## Community
- **GitHub**: [github.com/hyve-lang](https://github.com/broken-bytes/hyve)
- **Discord**: Join our [Hyve Discord Community](https://discord.gg/hyve-lang)
- **Twitter**: Follow us [@HyveLang](https://twitter.com/HyveLang) for updates and news.

## Contributing
We love contributions! If you're interested in contributing, please read our [Contributing Guide](https://github.com/hyve-lang/hyve/CONTRIBUTING.md).

## License
Hyve is open-sourced under the MIT License. See the [LICENSE](https://github.com/hyve-lang/hyve/LICENSE.md) file for details.

---

Happy Coding with Hyve!

Remember, since Hyve is a hobbyist language, expect missing features and bugs.
