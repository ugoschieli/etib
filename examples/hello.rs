use anyhow::Result;
use etib::*;

fn main() -> Result<()> {
    let (mut app, event_loop) = App::new();
    app.run(event_loop)?;

    Ok(())
}
