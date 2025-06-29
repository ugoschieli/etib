use anyhow::Result;
use env_logger;
use etib::*;
use log::info;

fn main() -> Result<()> {
    env_logger::init();
    info!("Initializing ETIB");

    let (mut app, event_loop) = Game::new();
    app.run(event_loop)?;

    Ok(())
}
