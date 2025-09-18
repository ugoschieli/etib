#![warn(missing_docs)]

//! The ETIB Game engine crate.

mod buffer;
mod camera;
mod gfx;
mod pipeline;
mod shader;
mod uniform;
mod vertex;
mod window;

pub use crate::gfx::*;
pub use crate::shader::*;
pub use crate::window::*;
